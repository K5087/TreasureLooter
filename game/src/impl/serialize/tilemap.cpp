module tilemap.serialize;

import handle;
import context;

import simdjson;
import std;

namespace simdjson {
void tag_invoke(serialize_tag tag, builder::string_builder &builder,
                const Handle<Tilemap> &payload) {
    tag_invoke(tag, builder, &*payload);
}

simdjson::error_code tag_invoke(deserialize_tag, ondemand::document &val,
                                Handle<Tilemap> &payload) {
    std::string_view value;
    auto error = val.get_string().get(value);
    if (error) {
        return error;
    }
    if (value.empty()) {
        return simdjson::SUCCESS;
    }
    auto &manager = Context::GetInst().m_tilemap_manager;
    payload = manager->Find(value);
    if (!payload) {
        payload = manager->Load(value);
    }
    return simdjson::SUCCESS;
}

simdjson::error_code tag_invoke(deserialize_tag, ondemand::value &val,
                                Handle<Tilemap> &payload) {
    std::string_view value;
    auto error = val.get_string().get(value);
    if (error) {
        return error;
    }
    if (value.empty()) {
        return simdjson::SUCCESS;
    }
    auto &manager = Context::GetInst().m_tilemap_manager;
    payload = manager->Find(value);
    if (!payload) {
        payload = manager->Load(value);
    }
    return simdjson::SUCCESS;
}

void tag_invoke(serialize_tag, builder::string_builder &builder,
                const Tilemap *payload) {
    std::string path = payload ? payload->GetFilename().string() : "";
    builder.append(path);
}

simdjson::error_code tag_invoke(deserialize_tag, ondemand::document &val,
                                const Tilemap *payload) {
    std::string_view value;
    auto error = val.get_string().get(value);
    if (error) {
        return error;
    }
    if (value.empty()) {
        return simdjson::SUCCESS;
    }
    auto &manager = Context::GetInst().m_tilemap_manager;
    auto handle = manager->Load(value);
    if (!handle) {
        return simdjson::UNINITIALIZED;
    }
    payload = handle.Get();
    return simdjson::SUCCESS;
}

simdjson::error_code tag_invoke(deserialize_tag, ondemand::value &val,
                                Tilemap *&payload) {
    std::string_view value;
    auto error = val.get_string().get(value);
    if (error) {
        return error;
    }
    if (value.empty()) {
        return simdjson::SUCCESS;
    }
    auto &manager = Context::GetInst().m_tilemap_manager;
    auto handle = manager->Load(value);
    if (!handle) {
        return simdjson::UNINITIALIZED;
    }
    payload = handle.Get();
    return simdjson::SUCCESS;
}
}  // namespace simdjson
