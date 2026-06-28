#pragma once

#include <flag.hpp>
#include <window.hpp>

#include <SDL3/SDL.h>

struct Vec2;
struct Rect;
struct Color;
struct Region;
struct Degrees;
class Image;

enum class Flip {
    None = SDL_FLIP_NONE,
    Horizontal = SDL_FLIP_HORIZONTAL,
    Vertical = SDL_FLIP_VERTICAL,
};

class Renderer {
public:
    Renderer(Window& window);
    Renderer(Renderer&&) = delete;
    Renderer(const Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    ~Renderer();

    void SetClearColor(const Color&);

    void DrawLine(const Vec2& p1, const Vec2& p2, const Color& color);
    void DrawRect(const Rect& r, const Color& color);
    void FillRect(const Rect& r, const Color& color);
    void DrawImage(const Image& image, const Region& src, const Region& dst,
                   Degrees rotation, const Vec2& center, Flags<Flip>);

    void Clear();
    void Present();

    SDL_Renderer* GetRenderer() const;

private:
    SDL_Renderer* m_renderer{};
    SDL_Color m_clear_color;

    void setRendererColor(const Color& color);
};
