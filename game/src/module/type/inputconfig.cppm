export module inputconfig;

import key;
import padkey;
import gamepad;
import mousekey;

import std;

export {
struct KeyboardInput {
    Key m_key;
    float m_scale;
};

struct GamepadButtonInput {
    GamepadButtonType m_button;
    float m_scale;
};

struct GamepadAxisInput {
    GamepadAxisType m_axis;
    float m_scale;
};

struct MouseButtonInput {
    MouseButtonType m_type;
    float m_scale;
};

struct InputActionConfig {
    std::string m_name;
    std::vector<Key> m_keyboard;
    std::vector<GamepadButtonType> m_gamepad;
};

struct InputAxisConfig {
    std::string m_name;

    std::vector<KeyboardInput> m_keyboard;
    std::vector<GamepadAxisInput> m_gamepad_axis;
    std::vector<GamepadButtonInput> m_gamepad_button;

    std::optional<float> m_mouse_vertical;
    std::optional<float> m_mouse_horizontal;
};

struct InputConfig {
    std::vector<InputActionConfig> m_action;
    std::vector<InputAxisConfig> m_axis;
};
}
