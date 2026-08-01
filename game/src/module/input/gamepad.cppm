module;
#include <SDL3/SDL.h>
export module gamepad;

import padkey;
import button;
import math;
import std;

export {
class GamepadButton : public Button {
public:
    friend class Gamepad;
    explicit GamepadButton(SDL_GamepadButton type);

    virtual bool IsPressing() const override;
    virtual bool IsReleasing() const override;
    virtual bool IsReleased() const override;
    virtual bool IsPressed() const override;

private:
    SDL_GamepadButton m_type;
    bool m_is_press = false;
    bool m_last_press = false;
    bool m_has_handled_event = false;

    void handleEvent(const SDL_GamepadButtonEvent &event);
    void update();

    SDL_GamepadButton GetType() const;
};

class GamepadAxis {
public:
    friend class Gamepad;
    explicit GamepadAxis(SDL_GamepadAxis type);
    float Value() const;

    SDL_GamepadAxis GetType() const;

private:
    SDL_GamepadAxis m_axis;
    float m_value;
    Vec2 m_position;
    Vec2 m_offset;
    void handleEvent(const SDL_GamepadAxisEvent &event);
};

class Gamepad {
public:
    friend class GamepadManager;
    explicit Gamepad(SDL_JoystickID id);

    SDL_JoystickID GetID() const;

    const GamepadButton &GetButton(GamepadButtonType button) const;
    const GamepadAxis &GetAxis(GamepadAxisType axis) const;

private:
    SDL_JoystickID m_id;
    std::array<std::unique_ptr<GamepadButton>, SDL_GAMEPAD_BUTTON_COUNT>
        m_buttons;
    std::array<std::unique_ptr<GamepadAxis>, SDL_GAMEPAD_AXIS_COUNT> m_axises;

    void handleEvent(const SDL_Event &event);
    void update();

    static GamepadButton InvalidButton;
    static GamepadAxis InvalidAxis;
};

class GamepadManager {
public:
    void HandleEvent(const SDL_Event &event);
    void Update();

    const std::unordered_map<SDL_JoystickID, Gamepad> &GetGamepads() const;

private:
    std::unordered_map<SDL_JoystickID, Gamepad> m_gamepads;
};
}
