module;
union SDL_Event;
export module context;

import gameobject;
import window;
import renderer;
import image;
import inspector;
import transform;
import sprite;
import relationship;
import entity;

import std;

export class Context {
public:
    static void Init();
    static void Destroy();
    static Context &GetInst();

    Context(Context &&) = delete;
    Context(const Context &) = delete;
    Context &operator=(Context &&) = delete;
    Context &operator=(const Context &) = delete;

    ~Context();

    void Update();
    void HandleEvents(const SDL_Event &);
    bool ShouldExit();

public:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<ImageManager> m_image_manager;
    std::unique_ptr<Inspector> m_inspector;
    std::unique_ptr<RelationshipManager> m_relation_manager;
    std::unique_ptr<TransformManager> m_transform_manager;
    std::unique_ptr<SpriteManager> m_sprite_manager;

private:
    static std::unique_ptr<Context> instance;
    bool m_should_exit = false;
    Entity m_last_entity = 0;
    Entity m_root_entity;

    GameObject m_root;

    Context();

    void logicUpdate();
    void renderUpdate();

    Entity createEntity();
};
