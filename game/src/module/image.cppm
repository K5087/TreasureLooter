module;
struct SDL_Renderer;
struct SDL_Texture;
export module image;

import path;
import math;

import std;

export class Image {
public:
    Image(SDL_Renderer &renderer, const Path &filename);
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

export class ImageManager {
public:
    explicit ImageManager(SDL_Renderer &renderer);

    Image *Load(const Path &filename);
    Image *Find(const Path &filename);
    bool IsExists(const Path &filename);

private:
    std::unordered_map<Path, std::unique_ptr<Image>> m_images;

    SDL_Renderer &m_renderer;
};
