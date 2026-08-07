module;
export module uuid.serialize;
export import uuid;

import simdjson;
import std;

export {
namespace simdjson {
void tag_invoke(serialize_tag, builder::string_builder &builder,
                const UUID &payload) {
    std::string path = payload.ToString();
    builder.append(simdjson::pad(path));
}

simdjson::error_code tag_invoke(deserialize_tag, ondemand::document &val,
                                UUID &payload) {
    std::string_view value;
    auto error = val.get_string().get(value);
    if (error) {
        return error;
    }

    payload = UUID::CreateFromString(value);

    return simdjson::SUCCESS;
}

simdjson::error_code tag_invoke(deserialize_tag, ondemand::value &val,
                                UUID &payload) {
    std::string_view value;
    auto error = val.get_string().get(value);
    if (error) {
        return error;
    }

    payload = UUID::CreateFromString(value);

    return simdjson::SUCCESS;
}
}  // namespace simdjson
}
