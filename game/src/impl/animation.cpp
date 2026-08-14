module;
#include <log.hpp>
module animation;

import log;
import uuid;
import context;

void Animation::Play() {
    m_is_playing = true;
}

void Animation::Pause() {
    m_is_playing = false;
}

void Animation::Stop() {
    Rewind();
    Pause();
}

void Animation::Rewind() {
    for (auto& [_, track] : m_tracks) {
        if (track) {
            track->Rewind();
        }
    }
}

void Animation::SetLoop(int count) {
    m_loop = count;
}

void Animation::Update(float delta_time) {
    if (!m_is_playing) {
        return;
    }
    m_cur_time += delta_time;
    for (auto& [_, track] : m_tracks) {
        if (track) {
            track->Update(delta_time);
        }
    }
    if (m_cur_time >= m_max_time) {
        if (m_loop > 0 || m_loop == InfLoop) {
            Rewind();
            m_cur_time = m_cur_time - m_max_time;

            if (m_loop != InfLoop) {
                m_loop--;
            }
        } else {
            Pause();
            m_cur_time = m_max_time;
        }
    }
}

#define FIND_TRACK(TrackType, Impl)                                       \
    if (auto it = m_tracks.find(TrackType); it != m_tracks.end()) {       \
        auto& track = it->second;                                         \
        switch (track->GetType()) {                                       \
            Impl default : LOGW("Unknow Track Type,Animation Sync Skip"); \
        }                                                                 \
    }

#define TRACK_TYPE_CASE(CaseType, Target)                                   \
    case CaseType: {                                                        \
        Target =                                                            \
            static_cast<const AnimationTrack<decltype(Target), CaseType>&>( \
                *track)                                                     \
                .GetValue();                                                \
        break;                                                              \
    }

void Animation::Sync(Entity entity) {
    auto& ctx = Context::GetInst();

    if (auto transform = ctx.m_transform_manager->Get(entity)) {
        FIND_TRACK(
            AnimationBindingPoint::TransformPosition,
            TRACK_TYPE_CASE(AnimationTrackType::Linear, transform->m_position);
            TRACK_TYPE_CASE(AnimationTrackType::Discrete,
                            transform->m_position));

        if (auto it = m_tracks.find(AnimationBindingPoint::TransformRotation);
            it != m_tracks.end()) {
            auto& track = it->second;
            switch (track->GetType()) {
                case AnimationTrackType::Linear: {
                    transform->m_rotation = static_cast<const AnimationTrack<
                        float, AnimationTrackType::Linear>&>(*track)
                                                .GetValue();
                    break;
                }
                case AnimationTrackType::Discrete: {
                    transform->m_rotation = static_cast<const AnimationTrack<
                        float, AnimationTrackType::Discrete>&>(*track)
                                                .GetValue();
                    break;
                }
                default:
                    LOGW("Unknow Track Type,Animation Sync Skip");
            }
        }
        FIND_TRACK(
            AnimationBindingPoint::TransformScale,
            TRACK_TYPE_CASE(AnimationTrackType::Linear, transform->m_scale);
            TRACK_TYPE_CASE(AnimationTrackType::Discrete, transform->m_scale));
    }
    if (auto sprite = ctx.m_sprite_manager->Get(entity)) {
        FIND_TRACK(
            AnimationBindingPoint::SpriteRegion,
            TRACK_TYPE_CASE(AnimationTrackType::Discrete, sprite->m_region));
        FIND_TRACK(
            AnimationBindingPoint::SpriteRegion,
            TRACK_TYPE_CASE(AnimationTrackType::Discrete, sprite->m_image););
        FIND_TRACK(
            AnimationBindingPoint::SpriteFlip,
            TRACK_TYPE_CASE(AnimationTrackType::Discrete, sprite->m_flip));

        FIND_TRACK(
            AnimationBindingPoint::SpriteSize,
            TRACK_TYPE_CASE(AnimationTrackType::Linear, sprite->m_size);
            TRACK_TYPE_CASE(AnimationTrackType::Discrete, sprite->m_size));
    }
}

int Animation::GetLoopCount() const {
    return m_loop;
}

void AnimationComponentManager::Update(TimeType delta_time) {
    for (auto& [entity, anim] : m_components) {
        anim->Update(delta_time);
        anim->Sync(entity);
    }
}

AnimationHandle AnimationManager::Create() {
    return store(nullptr, UUID::CreateV4(), std::make_unique<Animation>());
}
