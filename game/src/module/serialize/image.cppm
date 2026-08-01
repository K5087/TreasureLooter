module;
#include <log.hpp>
export module image.serialize;

export import image;

import simdjson;
import log;
import std;

export {
namespace simdjson {
void tag_invoke(serialize_tag, builder::string_builder &builder,
                const Image *payload) {
    std::string path = payload->Filename().string();
    builder.append(simdjson::pad(path));
}

auto tag_invoke(deserialize_tag, ondemand::value &val, Image *&payload) {
    std::string_view value;
    auto error = val.get_string().get(value);
    if (error) {
        return error;
    }

    payload = LoadImage(value);
    if (!payload) {
        LOGE("Failed to load image: {}", value);
        return simdjson::SUCCESS;
    }

    return simdjson::SUCCESS;
}
}  // namespace simdjson
}
