export module input;

import path;
import button;
import gamepad;
import inputconfig;
import keyboard;
import gamepad;

import std;

export {
class Action {
public:
    void AddButton(const Button& button);

    bool IsPressing() const;
    bool IsReleasing() const;
    bool IsReleased() const;
    bool IsPressed() const;

    bool IsRelease() const;
    bool IsPress() const;

private:
    std::vector<const Button*> m_buttons{};
};

class Axis {
public:
    void AddMapping(const Button& button, float scale);
    void AddMapping(const GamepadAxis& axis, float scale);
    void AddMouseHorizontalMapping(float scale);
    void AddMouseVerticalMapping(float scale);

    float Value() const;

private:
    struct ButtonMapping {
        const Button* m_button{};
        float m_scale = 1.0f;
    };

    struct AxisMapping {
        const GamepadAxis* m_axis{};
        float m_scale = 1.0f;
    };

    struct MouseMapping {
        float m_scale = 1.0f;
    };

    std::vector<ButtonMapping> m_button_mappings;
    std::vector<AxisMapping> m_axis_mappings;
    std::optional<MouseMapping> m_horizontal;
    std::optional<MouseMapping> m_vertical;
};

class InputManager {
public:
    explicit InputManager(Keyboard* keyboard, GamepadManager* gamepad_manager,
                          const Path& config_path);

    const Axis& GetAxis(const std::string& name);
    const Action& GetAction(const std::string& name);

    void SetConfig(Keyboard* keyboard, GamepadManager* gamepad_manager,
                   const InputConfig& config);

private:
    std::unordered_map<std::string, Axis> m_axis_mapping;
    std::unordered_map<std::string, Action> m_action_mapping;

    void loadAxisConfig(Keyboard* keyboard, GamepadManager* gamepad_manager,
                        const InputAxisConfig& axis);
    void loadActionConfig(Keyboard* keyboard, GamepadManager* gamepad_manager,
                          const InputActionConfig& action);
    static Action InvalidAction;
    static Axis InvalidAxis;
};
}
