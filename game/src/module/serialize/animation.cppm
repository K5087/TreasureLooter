export module animation.serialize;

export import animation;
export import animation.type.serialize;

import simdjson;
import std;

export {
namespace simdjson {
void tag_invoke(serialize_tag, builder::string_builder& builder,
                const Animation& payload);

simdjson::error_code tag_invoke(deserialize_tag, ondemand::document& val,
                                Animation& payload);
simdjson::error_code tag_invoke(deserialize_tag, ondemand::value& val,
                                Animation& payload);

// Keyframe
template <typename T>
void tag_invoke(serialize_tag, builder::string_builder& builder,
                const KeyFrame<T>& payload) {
    builder.start_object();
    builder.template append_key_value<"time">(payload.m_time);
    builder.append_comma();
    builder.template append_key_value<"value">(payload.m_value);
    builder.end_object();
}

template <typename T>
simdjson::error_code tag_invoke(deserialize_tag, ondemand::document& val,
                                KeyFrame<T>& payload) {
    ondemand::object obj;
    auto error = val.get_object().get(obj);
    if (error) {
        return error;
    }

    if ((error = obj["time"].get(payload.m_time))) {
        return error;
    }
    if ((error = obj["value"].get(payload.m_value))) {
        return error;
    }

    return simdjson::SUCCESS;
}

template <typename T>
simdjson::error_code tag_invoke(deserialize_tag, ondemand::value& val,
                                KeyFrame<T>& payload) {
    ondemand::object obj;
    auto error = val.get_object().get(obj);

    if (error) {
        return error;
    }

    if ((error = obj["time"].get(payload.m_time))) {
        return error;
    }
    if ((error = obj["value"].get(payload.m_value))) {
        return error;
    }

    return simdjson::SUCCESS;
}
}  // namespace simdjson
}
