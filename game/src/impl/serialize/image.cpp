module;
#include <log.hpp>
module image.serialize;

import simdjson;
import context;
import log;

import std;

namespace simdjson {
void tag_invoke(serialize_tag, builder::string_builder &builder,
                const Image *payload) {
    std::string path = payload ? payload->Filename().string() : "";
    builder.append(path);
}

simdjson::error_code tag_invoke(deserialize_tag, ondemand::document &val,
                                Image *&payload) {
    std::string_view value;
    auto error = val.get_string().get(value);
    if (error) {
        return error;
    }

    auto &image_manager = Context::GetInst().m_image_manager;
    ImageHandle handle = image_manager->Load(value);

    if (handle) {
        payload = handle.Get();
    }

    if (!payload) {
        LOGE("Failed to load image: {}", value);
        return simdjson::SUCCESS;
    }

    return simdjson::SUCCESS;
}

simdjson::error_code tag_invoke(deserialize_tag, ondemand::value &val,
                                Image *&payload) {
    std::string_view value;
    auto error = val.get_string().get(value);
    if (error) {
        return error;
    }

    auto &image_manager = Context::GetInst().m_image_manager;
    ImageHandle handle = image_manager->Load(value);

    if (handle) {
        payload = handle.Get();
    }

    if (!payload) {
        LOGE("Failed to load image: {}", value);
        return simdjson::SUCCESS;
    }

    return simdjson::SUCCESS;
}

void tag_invoke(serialize_tag tag, builder::string_builder &builder,
                const Handle<Image> &payload) {
    tag_invoke(tag, builder, &*payload);
}

simdjson::error_code tag_invoke(deserialize_tag tag, ondemand::document &val,
                                Handle<Image> &payload) {
    std::string_view value;
    auto error = val.get_string().get(value);
    if (error) {
        return error;
    }

    auto &image_manager = Context::GetInst().m_image_manager;
    ImageHandle handle = image_manager->Find(value);
    if (!handle) {
        payload = image_manager->Load(value);
    } else {
        payload = handle;
    }

    if (!payload) {
        LOGE("Failed to load image: {}", value);
        return simdjson::SUCCESS;
    }

    return simdjson::SUCCESS;
}

simdjson::error_code tag_invoke(deserialize_tag tag, ondemand::value &val,
                                Handle<Image> &payload) {
    std::string_view value;
    auto error = val.get_string().get(value);
    if (error) {
        return error;
    }

    auto &image_manager = Context::GetInst().m_image_manager;
    ImageHandle handle = image_manager->Find(value);
    if (!handle) {
        payload = image_manager->Load(value);
    } else {
        payload = handle;
    }

    if (!payload) {
        LOGE("Failed to load image: {}", value);
        return simdjson::SUCCESS;
    }

    return simdjson::SUCCESS;
}
}  // namespace simdjson
