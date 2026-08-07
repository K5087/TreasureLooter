module;
#include <log.hpp>

#include <SDL3/SDL.h>
export module image;

export import handle;

import log;
import path;
import math;
import asset.manager;

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

using ImageHandle = Handle<Image>;

class ImageManager : public AssetManagerBase<Image> {
public:
    explicit ImageManager(SDL_Renderer &renderer);

    ImageHandle Load(const Path &filename);

private:
    SDL_Renderer &m_renderer;
};
}
