module;
struct SDL_Renderer;
struct SDL_Texture;
export module image;

import path;
import math;
import simdjson;
import log;

import std;
export {
class Image {
public:
    Image(SDL_Renderer &renderer, const Path &filename);
    Image(Image &&) = delete;
    Image(const Image &) = delete;
    Image &operator=(Image &&) = delete;
    Image &operator=(const Image &) = delete;
    ~Image();

    Vec2 GetSize() const;

    SDL_Texture *GetTexture() const;

    const Path &Filename() const;

private:
    SDL_Texture *m_texture{};
    Path m_filename;
};

class ImageManager {
public:
    explicit ImageManager(SDL_Renderer &renderer);

    Image *Load(const Path &filename);
    Image *Find(const Path &filename);
    bool IsExists(const Path &filename);

private:
    std::unordered_map<Path, std::unique_ptr<Image>> m_images;

    SDL_Renderer &m_renderer;
};

Image *LoadImage(const Path &filename);

namespace simdjson {
template <typename builder_type>
void tag_invoke(serialize_tag, builder_type &builder, const Image *payload) {
    std::string path = payload->Filename().string();
    builder.append(simdjson::pad(path));
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Image *&payload) {
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
