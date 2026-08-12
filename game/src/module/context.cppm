module;
#include <SDL3/SDL.h>
export module context;

import path;
import prefab;
import editor;
import window;
import renderer;
import image;
import inspector;
import entity;
import keyboard;
import mouse;
import finger_touch;
import gamepad;
import input;
import tilemap;
import animation;
import time;
import asset.manager;

import sprite.manager;
import transform.manager;
import relationship.manager;

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
#ifdef TL_ENABLE_EDITOR
    std::unique_ptr<Editor> m_editor;
#endif
    std::unique_ptr<RelationshipManager> m_relation_manager;
    std::unique_ptr<TransformManager> m_transform_manager;

    std::unique_ptr<TilemapManager> m_tilemap_manager;
    std::unique_ptr<TilemapComponentManager> m_tilemap_component_manager;
    std::unique_ptr<SpriteManager> m_sprite_manager;
    std::unique_ptr<Keyboard> m_keyboard;
    std::unique_ptr<Mouse> m_mouse;
    std::unique_ptr<Touch> m_touch;
    std::unique_ptr<GamepadManager> m_gamepad_manager;
    std::unique_ptr<InputManager> m_input_manager;
    std::unique_ptr<GenericAssetsManager> m_generic_assets_manager;
    std::unique_ptr<Time> m_time;
    std::unique_ptr<AnimationManager> m_anim_manager;

    Entity GetRootEntity();

#ifdef TL_ENABLE_EDITOR
    const Path &GetProjectPath() const;
#endif

    void RegisterEntity(const EntityInstance &);
    void RemoveEntity(Entity);

private:
    static std::unique_ptr<Context> instance;
    bool m_should_exit = false;
    Entity m_last_entity = 0;
    Entity m_root_entity;

    Context();

    void logicUpdate();
    void gameLogicUpdate();
    void logicPostUpdate();
    void renderUpdate();
    Entity createEntity();
};
