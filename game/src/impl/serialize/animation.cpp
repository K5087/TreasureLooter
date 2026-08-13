module animation.serialize;

import simdjson;
import std;

namespace simdjson {
void SerializeTrack(builder::string_builder& builder,
                    const AnimationTrackBase& payload) {
    builder.start_object();
    builder.template append_key_value<"type">(payload.GetType());
    builder.append_comma();
    switch (payload.GetType()) {
        case AnimationTrackType::Linear: {
            auto& keyframes =
                static_cast<
                    const AnimationTrack<float, AnimationTrackType::Linear>&>(
                    payload)
                    .GetKeyFrames();
            builder.template append_key_value<"keyframes">(keyframes);
            break;
        }
        case AnimationTrackType::Discrete: {
            auto& keyframes =
                static_cast<
                    const AnimationTrack<float, AnimationTrackType::Discrete>&>(
                    payload)
                    .GetKeyFrames();
            builder.template append_key_value<"keyframes">(keyframes);
            break;
        }
    }
    builder.end_object();
}

void tag_invoke(serialize_tag, builder::string_builder& builder,
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

        SerializeTrack(builder, *track);
    }
    builder.end_object();
    builder.template append_key_value<"loop">(payload.GetLoopCount());
    builder.end_object();
}

simdjson::error_code tag_invoke(deserialize_tag, ondemand::document& val,
                                Animation& payload) {
    ondemand::object obj;
    auto error = val.get_object().get(obj);
    if (error) {
        return error;
    }

    if ((error = obj["tracks"].get(payload.m_tracks))) {
        return error;
    }
    if ((error = obj["loop"].get(payload.m_loop))) {
        return error;
    }

    return simdjson::SUCCESS;
}

simdjson::error_code tag_invoke(deserialize_tag, ondemand::value& val,
                                Animation& payload) {
    ondemand::object obj;
    auto error = val.get_object().get(obj);
    if (error) {
        return error;
    }

    if ((error = obj["tracks"].get(payload.m_tracks))) {
        return error;
    }
    if ((error = obj["loop"].get(payload.m_loop))) {
        return error;
    }

    return simdjson::SUCCESS;
}
}  // namespace simdjson
