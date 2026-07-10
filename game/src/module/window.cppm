module;
struct SDL_Window;
export module window;

import math;
import std;

export class Window {
public:
    Window(const std::string& title, int w, int h);
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    ~Window();

    Vec2 GetWindowSize() const;

    SDL_Window* GetWindow();

private:
    SDL_Window* m_window{};
};
