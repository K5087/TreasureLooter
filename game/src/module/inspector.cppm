module;
union SDL_Event;
export module inspector;

import window;
import renderer;
import entity;

import std;

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
    bool m_hierarchy_window_open = true;
    bool m_detail__window_open = true;

    std::optional<Entity> m_selected_entity;

    void showEntityHierarchy(Entity entity);
    void showEntityDetail(Entity entity)
};
