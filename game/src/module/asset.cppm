module;
export module asset;

import path;
import storage;
import serialize;

import std;

export {
template <typename T>
T LoadAsset(const Path& filename) {
    auto file = IOStream::CreateFromFile(filename, IOMode::Read, true);
    auto context = file->Read();
    std::string json(context.begin(), context.end());
    T object;
    Deserialize(json, object);
    return object;
}

template <typename T>
void SaveAsset(const T& object, const Path& filename) {
    auto file = IOStream::CreateFromFile(filename, IOMode::Write, true);
    std::string json = Serialize(object);
    file->Write(json.c_str(), json.size());
}
}
