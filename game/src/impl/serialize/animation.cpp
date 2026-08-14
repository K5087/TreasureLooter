module;
#include <log.hpp>
module animation.serialize;

import log;
import flag;

import serialize;
import flip.serialize;
import math.serialize;
import image.serialize;

import simdjson;
import std;

#define SERIALIZE_KEYFRAMES(CaseType, TargetType, Payload)                \
    auto& keyframes =                                                     \
        static_cast<const AnimationTrack<TargetType, CaseType>&>(Payload) \
            .GetKeyFrames();                                              \
    builder.template append_key_value<"keyframes">(keyframes);            \
    break;

#define DESERIALIZE_KEYFRAMES(CaseType, TargetType)                        \
    auto track = std::make_unique<AnimationTrack<TargetType, CaseType>>(); \
    std::vector<KeyFrame<TargetType>> keyframes;                           \
    if ((error = obj["keyframes"].get(keyframes))) {                       \
        return error;                                                      \
    }                                                                      \
    for (auto& keyframe : keyframes) {                                     \
        track->AddKeyFrame(keyframe);                                      \
    }                                                                      \
    payload.AddTrack(bindpoint, std::move(track));                         \
    break;

#define TRACK_TYPE_CASE(CaseType, CaseImpl) \
    case CaseType: {                        \
        CaseImpl                            \
    }

#define SERIALIZE_TRACK(TargetType, Payload)                                  \
    TRACK_TYPE_CASE(                                                          \
        AnimationTrackType::Linear,                                           \
        SERIALIZE_KEYFRAMES(AnimationTrackType::Linear, TargetType, Payload)) \
    TRACK_TYPE_CASE(AnimationTrackType::Discrete,                             \
                    SERIALIZE_KEYFRAMES(AnimationTrackType::Discrete,         \
                                        TargetType, Payload))

#define DESERIALIZE_TRACK(TargetType)                                  \
    TRACK_TYPE_CASE(                                                   \
        AnimationTrackType::Linear,                                    \
        DESERIALIZE_KEYFRAMES(AnimationTrackType::Linear, TargetType)) \
    TRACK_TYPE_CASE(                                                   \
        AnimationTrackType::Discrete,                                  \
        DESERIALIZE_KEYFRAMES(AnimationTrackType::Discrete, TargetType))

namespace simdjson {
void tag_invoke(serialize_tag tag, builder::string_builder& builder,
                const Animation& payload) {
    builder.start_object();
    builder.template escape_and_append_with_quotes<"tracks">();
    builder.append_colon();
    builder.start_object();
    bool first = true;
    for (auto& [bindpoint, track] : payload.GetTracks()) {
        if (first) {
            first = false;
        } else {
            builder.append_comma();
        }

        builder.append(bindpoint);
        builder.append_colon();

        builder.start_object();
        builder.template append_key_value<"type">(track->GetType());
        builder.append_comma();
        switch (bindpoint) {
            case AnimationBindingPoint::TransformPosition:
                switch (track->GetType()) { SERIALIZE_TRACK(Vec2, *track); }
                break;
            case AnimationBindingPoint::TransformRotation:
                switch (track->GetType()) { SERIALIZE_TRACK(float, *track); }
                break;
            case AnimationBindingPoint::TransformScale:
                switch (track->GetType()) { SERIALIZE_TRACK(Vec2, *track); }
                break;
            case AnimationBindingPoint::SpriteRegion: {
                SERIALIZE_KEYFRAMES(AnimationTrackType::Discrete, Region,
                                    *track);
            }
            case AnimationBindingPoint::SpriteImage: {
                SERIALIZE_KEYFRAMES(AnimationTrackType::Discrete, ImageHandle,
                                    *track);
            }
            case AnimationBindingPoint::SpriteFlip: {
                SERIALIZE_KEYFRAMES(AnimationTrackType::Discrete, Flags<Flip>,
                                    *track);
            }
            case AnimationBindingPoint::SpriteSize:
                switch (track->GetType()) { SERIALIZE_TRACK(Vec2, *track); }
                break;
            default:
                LOGE("Unknown Bindpoint Type,Serialize Failed");
        }

        builder.end_object();
    }
    builder.end_object();
    builder.append_comma();
    builder.template append_key_value<"loop">(payload.GetLoopCount());
    builder.end_object();
}

simdjson::error_code tag_invoke(deserialize_tag tag, ondemand::document& val,
                                Animation& payload) {
    ondemand::object obj;
    auto error = val.get_object().get(obj);
    if (error) {
        return error;
    }

    ondemand::object tracks;
    if ((error = obj["tracks"].get_object().get(tracks))) {
        return error;
    }
    for (auto field : tracks) {
        AnimationBindingPoint bindpoint;
        std::string bindpoint_str;
        if ((error = field.unescaped_key().get(bindpoint_str))) {
            return error;
        }
        Deserialize(bindpoint_str, bindpoint);
        // std::unique_ptr<AnimationTrackBase> track;

        ondemand::object track_obj;
        if ((error = field.value().get(track_obj))) {
            return error;
        }
        AnimationTrackType type;
        if ((error = obj["type"].get(type))) {
            return error;
        }
        switch (bindpoint) {
            case AnimationBindingPoint::TransformPosition:
                switch (type) { DESERIALIZE_TRACK(Vec2); }
                break;
            case AnimationBindingPoint::TransformRotation:
                switch (type) { DESERIALIZE_TRACK(float); }
                break;
            case AnimationBindingPoint::TransformScale:
                switch (type) { DESERIALIZE_TRACK(Vec2); }
                break;
            case AnimationBindingPoint::SpriteRegion: {
                DESERIALIZE_KEYFRAMES(AnimationTrackType::Discrete, Region);
            }
            case AnimationBindingPoint::SpriteImage: {
                DESERIALIZE_KEYFRAMES(AnimationTrackType::Discrete,
                                      ImageHandle);
            }
            case AnimationBindingPoint::SpriteFlip: {
                DESERIALIZE_KEYFRAMES(AnimationTrackType::Discrete,
                                      Flags<Flip>);
            }
            case AnimationBindingPoint::SpriteSize:
                switch (type) { DESERIALIZE_TRACK(Vec2); }
                break;
            default:
                LOGE("Unknown Bindpoint Type,Deserialize Failed");
        }
    }

    int loop = 0;
    if ((error = obj["loop"].get(loop))) {
        return error;
    }
    payload.SetLoop(loop);

    return simdjson::SUCCESS;
}

simdjson::error_code tag_invoke(deserialize_tag, ondemand::value& val,
                                Animation& payload) {
    ondemand::object obj;
    auto error = val.get_object().get(obj);
    if (error) {
        return error;
    }

    ondemand::object tracks;
    if ((error = obj["tracks"].get_object().get(tracks))) {
        return error;
    }
    for (auto field : tracks) {
        AnimationBindingPoint bindpoint;
        std::string bindpoint_str;
        if ((error = field.unescaped_key().get(bindpoint_str))) {
            return error;
        }
        Deserialize(bindpoint_str, bindpoint);
        // std::unique_ptr<AnimationTrackBase> track;

        ondemand::object track_obj;
        if ((error = field.value().get(track_obj))) {
            return error;
        }
        AnimationTrackType type;
        if ((error = obj["type"].get(type))) {
            return error;
        }
        switch (bindpoint) {
            case AnimationBindingPoint::TransformPosition:
                switch (type) { DESERIALIZE_TRACK(Vec2); }
                break;
            case AnimationBindingPoint::TransformRotation:
                switch (type) { DESERIALIZE_TRACK(float); }
                break;
            case AnimationBindingPoint::TransformScale:
                switch (type) { DESERIALIZE_TRACK(Vec2); }
                break;
            case AnimationBindingPoint::SpriteRegion: {
                DESERIALIZE_KEYFRAMES(AnimationTrackType::Discrete, Region);
            }
            case AnimationBindingPoint::SpriteImage: {
                DESERIALIZE_KEYFRAMES(AnimationTrackType::Discrete,
                                      ImageHandle);
            }
            case AnimationBindingPoint::SpriteFlip: {
                DESERIALIZE_KEYFRAMES(AnimationTrackType::Discrete,
                                      Flags<Flip>);
            }
            case AnimationBindingPoint::SpriteSize:
                switch (type) { DESERIALIZE_TRACK(Vec2); }
                break;
            default:
                LOGE("Unknown Bindpoint Type,Deserialize Failed");
        }
    }

    int loop = 0;
    if ((error = obj["loop"].get(loop))) {
        return error;
    }
    payload.SetLoop(loop);

    return simdjson::SUCCESS;
}
}  // namespace simdjson
