module;
#include <log.hpp>
#include <sdl_call.hpp>
#include <stb_image.h>

#include <SDL3/SDL.h>
module image;

import log;
import math;
import renderer;
import storage;
import context;

Image::Image(SDL_Renderer &renderer, const Path &filename)
    : m_filename(filename) {
    int w, h;

    auto file = IOStream::CreateFromFile(filename, IOMode::Read, true);
    auto content = file->Read();

    stbi_uc *data =
        stbi_load_from_memory((const stbi_uc *)content.data(), content.size(),
                              &w, &h, nullptr, STBI_rgb_alpha);
    if (!data) {
        LOGE("load image {} failed", filename);
        return;
    }

    SDL_Surface *surface =
        SDL_CreateSurfaceFrom(w, h, SDL_PIXELFORMAT_RGBA32, data, w * 4);
    if (!surface) {
        LOGE("create SDL surface from {} failed: {}", filename, SDL_GetError());
        stbi_image_free(data);
        return;
    }
    m_texture = SDL_CreateTextureFromSurface(&renderer, surface);
    if (!m_texture) {
        LOGE("create SDL texture from {} failed: {}", filename, SDL_GetError());
        stbi_image_free(data);
        SDL_DestroySurface(surface);
        return;
    }

    SDL_DestroySurface(surface);
    SDL_CALL(SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND));
    stbi_image_free(data);
    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
}

Image::~Image() {
    SDL_DestroyTexture(m_texture);
}

Vec2 Image::GetSize() const {
    Vec2 size;
    SDL_CALL(SDL_GetTextureSize(m_texture, &size.w, &size.h));
    return size;
}

SDL_Texture *Image::GetTexture() const {
    return m_texture;
}

const Path &Image::Filename() const {
    return m_filename;
}

ImageManager::ImageManager(SDL_Renderer &renderer) : m_renderer(renderer) {}

Image *ImageManager::Load(const Path &filename) {
    if (auto it = m_images.find(filename); it != m_images.end()) {
        LOGW("image {} already loaded", filename);
        return it->second.get();
    }
    auto result = m_images.emplace(
        filename, std::make_unique<Image>(m_renderer, filename));
    if (!result.second) {
        LOGE("emplace image failed");
        return nullptr;
    }
    return result.first->second.get();
}

Image *ImageManager::Find(const Path &filename) {
    if (auto it = m_images.find(filename); it != m_images.end()) {
        return it->second.get();
    }
    return nullptr;
}

bool ImageManager::IsExists(const Path &filename) {
    return Find(filename);
}

Image *LoadImage(const Path &filename) {
    auto &image_manager = Context::GetInst().m_image_manager;
    Image *image = image_manager->Find(filename);

    if (!image && !filename.empty()) {
        image = image_manager->Load(filename);
    }
    return image;
}
