module;
union SDL_Event;
export module inspector;

import std;

import window;
import renderer;

export class Inspector {
public:
    Inspector(Window& window, Renderer& renderer);
    ~Inspector();

    void BeginFrame();
    void EndFrame();
    void Update();

    void HandleEvents(const SDL_Event& event);

private:
    Window& m_window;
    Renderer& m_renderer;
};
