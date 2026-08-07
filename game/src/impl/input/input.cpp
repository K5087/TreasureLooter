module input;

import asset;
import context;
import inputconfig.serialize;

import std;

Action InputManager::InvalidAction;
Axis InputManager::InvalidAxis;

void Action::AddButton(const Button& button) {
    m_buttons.push_back(&button);
}

bool Action::IsPressing() const {
    return std::any_of(
        m_buttons.begin(), m_buttons.end(),
        [](const Button* const button) { return button->IsPressing(); });
}

bool Action::IsReleasing() const {
    return std::any_of(
        m_buttons.begin(), m_buttons.end(),
        [](const Button* const button) { return button->IsReleasing(); });
}

bool Action::IsReleased() const {
    return std::any_of(
        m_buttons.begin(), m_buttons.end(),
        [](const Button* const button) { return button->IsReleased(); });
}

bool Action::IsPressed() const {
    return std::any_of(
        m_buttons.begin(), m_buttons.end(),
        [](const Button* const button) { return button->IsPressed(); });
}

bool Action::IsRelease() const {
    return IsReleasing() || IsReleased();
}

bool Action::IsPress() const {
    return IsPressed() || IsPressing();
}

void Axis::AddMapping(const Button& button, float scale) {
    m_button_mappings.push_back({&button, scale});
}

void Axis::AddMapping(const GamepadAxis& axis, float scale) {
    m_axis_mappings.push_back({&axis, scale});
}

void Axis::AddMouseHorizontalMapping(float scale) {
    m_horizontal = MouseMapping{scale};
}

void Axis::AddMouseVerticalMapping(float scale) {
    m_vertical = MouseMapping{scale};
}

float Axis::Value() const {
    float value = 0;
    for (auto& mapping : m_button_mappings) {
        if (mapping.m_button->IsPress()) {
            value += mapping.m_scale;
        }
    }
    for (auto& mapping : m_axis_mappings) {
        value += mapping.m_axis->Value() * mapping.m_scale;
    }
    return value;
}

InputManager::InputManager(Keyboard* keyboard, GamepadManager* gamepad_manager,
                           const Path& config_path) {
    InputConfig config = LoadAsset<InputConfig>(config_path).m_payload;
    SetConfig(keyboard, gamepad_manager, config);
}

void InputManager::SetConfig(Keyboard* keyboard,
                             GamepadManager* gamepad_manager,
                             const InputConfig& config) {
    for (auto& axis : config.m_axis) {
        loadAxisConfig(keyboard, gamepad_manager, axis);
    }
    for (auto& action : config.m_action) {
        loadActionConfig(keyboard, gamepad_manager, action);
    }
}

const Axis& InputManager::GetAxis(const std::string& name) {
    if (auto it = m_axis_mapping.find(name); it != m_axis_mapping.end()) {
        return it->second;
    }
    return InvalidAxis;
}

const Action& InputManager::GetAction(const std::string& name) {
    if (auto it = m_action_mapping.find(name); it != m_action_mapping.end()) {
        return it->second;
    }

    return InvalidAction;
}

void InputManager::loadAxisConfig(Keyboard* keyboard,
                                  GamepadManager* gamepad_manager,
                                  const InputAxisConfig& config) {
    Axis axis;

    for (auto& input : config.m_keyboard) {
        auto& button = keyboard->Get(input.m_key);
        axis.AddMapping(button, input.m_scale);
    }

    if (config.m_mouse_horizontal) {
        axis.AddMouseHorizontalMapping(config.m_mouse_horizontal.value());
    }
    if (config.m_mouse_vertical) {
        axis.AddMouseHorizontalMapping(config.m_mouse_vertical.value());
    }

    // FIXME: will not register when gamepad not found
    if (!gamepad_manager->GetGamepads().empty()) {
        for (auto& input : config.m_gamepad_axis) {
            auto& gamepad = gamepad_manager->GetGamepads().begin()->second;
            axis.AddMapping(gamepad.GetAxis(input.m_axis), input.m_scale);
        }
        for (auto& input : config.m_gamepad_button) {
            auto& gamepad = gamepad_manager->GetGamepads().begin()->second;
            axis.AddMapping(gamepad.GetButton(input.m_button), input.m_scale);
        }
    }
    m_axis_mapping.emplace(config.m_name, axis);
}

void InputManager::loadActionConfig(Keyboard* keyboard,
                                    GamepadManager* gamepad_manager,
                                    const InputActionConfig& config) {
    Action action;
    for (auto& key : config.m_keyboard) {
        action.AddButton(keyboard->Get(key));
    }

    // FIXME: will not register when gamepad not found
    if (!gamepad_manager->GetGamepads().empty()) {
        auto& gamepad = gamepad_manager->GetGamepads().begin()->second;
        for (auto& button : config.m_gamepad) {
            action.AddButton(gamepad.GetButton(button));
        }
    }
    m_action_mapping.emplace(config.m_name, action);
}
