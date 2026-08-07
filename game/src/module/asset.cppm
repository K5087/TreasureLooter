export module asset;

export import uuid.serialize;

import path;
import storage;
import serialize;

import simdjson;
import std;

export {
template <typename T>
struct AssetLoadResult {
    UUID m_uuid;
    T m_payload;
};

template <typename T>
AssetLoadResult<T> LoadAsset(const Path &filename) {
    auto file = IOStream::CreateFromFile(filename, IOMode::Read, true);
    auto context = file->Read();
    std::string json(context.begin(), context.end());
    AssetLoadResult<T> object;
    Deserialize(json, object);
    return object;
}

template <typename T>
void SaveAsset(const UUID &uuid, const T &object, const Path &filename) {
    AssetLoadResult<T> asset;
    asset.m_uuid = uuid;
    asset.m_payload = object;
    auto file = IOStream::CreateFromFile(filename, IOMode::Write, true);
    std::string json = Serialize(asset);
    file->Write(json.c_str(), json.size());
}

namespace simdjson {

template <typename T>
void tag_invoke(serialize_tag, builder::string_builder &builder,
                const AssetLoadResult<T> &payload) {
    builder.start_object();
    builder.template append_key_value<"uuid">(payload.m_uuid);
    builder.append_comma();
    builder.template append_key_value<"payload">(payload.m_payload);
    builder.end_object();
}

template <typename T>
auto tag_invoke(deserialize_tag, ondemand::document &val,
                AssetLoadResult<T> &payload) {
    ondemand::object obj;
    auto error = val.get_object().get(obj);
    if (error) {
        return error;
    }
    if ((error = obj["uuid"].get(payload.m_uuid))) {
        return error;
    }

    if ((error = obj["payload"].get(payload.m_payload))) {
        return error;
    }
    return simdjson::SUCCESS;
}

template <typename T>
auto tag_invoke(deserialize_tag, ondemand::value &val,
                AssetLoadResult<T> &payload) {
    ondemand::object obj;
    auto error = val.get_object().get(obj);
    if (error) {
        return error;
    }
    if ((error = obj["uuid"].get(payload.m_uuid))) {
        return error;
    }

    if ((error = obj["payload"].get(payload.m_payload))) {
        return error;
    }
    return simdjson::SUCCESS;
}
}  // namespace simdjson
}
