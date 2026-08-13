module animation;

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

#define BEGIN_BINDING_POINT(binding)                                       \
    if (auto it = m_tracks.find(AnimationBindingPoint::TransformPosition); \
        it != m_tracks.end())

#define handle_linear_track()                                               \
    if (it->second->gettype() == AnimationTrackType::Linear) {              \
        binding_target =                                                    \
            static_cast<const AnimationTrack<decltype(binding_target),      \
                                             AnimationTrackType::Linear>&>( \
                *it->second)                                                \
                .getvalue();                                                \
    }
#define handle_discrete_track()                                               \
    if (it->second->gettype() == AnimationTrackType::Discrete) {              \
        binding_target =                                                      \
            static_cast<const AnimationTrack<decltype(binding_target),        \
                                             AnimationTrackType::Discrete>&>( \
                *it->second)                                                  \
                .getvalue();                                                  \
    }

void Animation::Sync(Entity entity) {
    auto& ctx = Context::GetInst();

    if (auto transform = ctx.m_transform_manager->Get(entity)) {
        // #define BINDING_TARGET transform->m_position
        //         BEGIN_BINDING_POINT(AnimationBindingPoint::TransformPosition)
        //         {
        //             HANDLE_LINEAR_TRACK();
        //             HANDLE_DISCRETE_TRACK();
        //         }
        // #undef BINDING_TARGET
        //
        // #define BINDING_TARGET transform->m_scale
        //         BEGIN_BINDING_POINT(AnimationBindingPoint::TransformScale) {
        //             HANDLE_LINEAR_TRACK();
        //             HANDLE_DISCRETE_TRACK();
        //         }
        // #undef BINDING_TARGET
        //
        // #define BINDING_TARGET transform->m_rotation
        //         BEGIN_BINDING_POINT(AnimationBindingPoint::TransformRotation)
        //         {
        //             HANDLE_LINEAR_TRACK();
        //             HANDLE_DISCRETE_TRACK();
        //         }
        // #undef BINDING_TARGET
        //     }
        //
        //     if (auto sprite = ctx.m_sprite_manager->Get(entity)) {
        // #define BINDING_TARGET sprite->m_image
        //         BEGIN_BINDING_POINT(AnimationBindingPoint::SpriteImage) {
        //             HANDLE_DISCRETE_TRACK();
        //         }
        // #undef BINDING_TARGET
        //
        // #define BINDING_TARGET sprite->m_region
        //         BEGIN_BINDING_POINT(AnimationBindingPoint::SpriteRegion) {
        //             HANDLE_DISCRETE_TRACK();
        //         }
        // #undef BINDING_TARGET
        //
        // #define BINDING_TARGET sprite->m_size
        //         BEGIN_BINDING_POINT(AnimationBindingPoint::SpriteSize) {
        //             HANDLE_LINEAR_TRACK();
        //             HANDLE_DISCRETE_TRACK();
        //         }
        // #undef BINDING_TARGET
        //
        // #define BINDING_TARGET sprite->m_flip
        //         BEGIN_BINDING_POINT(AnimationBindingPoint::SpriteFlip) {
        //             HANDLE_DISCRETE_TRACK();
        //         }
        // #undef BINDING_TARGET
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
