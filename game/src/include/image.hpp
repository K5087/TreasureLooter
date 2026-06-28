#pragma once

#include <path.hpp>

#include <SDL3/SDL.h>

#include <unordered_map>

struct Vec2;
class Renderer;

class Image {
public:
    Image(Renderer &renderer, const Path &filename);
    Image(Image &&) = delete;
    Image(const Image &) = delete;
    Image &operator=(Image &&) = delete;
    Image &operator=(const Image &) = delete;
    ~Image();

    Vec2 GetSize() const;

    SDL_Texture *GetTexture() const;

private:
    SDL_Texture *m_texture{};
};

class ImageManager {
public:
    explicit ImageManager(Renderer &renderer);

    Image *Load(const Path &filename);
    Image *Find(const Path &filename);
    bool IsExists(const Path &filename);

private:
    std::unordered_map<Path, std::unique_ptr<Image>> m_images;

    Renderer &m_renderer;
};
