module;
#include <SDL3/SDL.h>
module gamepad;

import std;

GamepadButton Gamepad::InvalidButton{SDL_GAMEPAD_BUTTON_INVALID};
GamepadAxis Gamepad::InvalidAxis{SDL_GAMEPAD_AXIS_INVALID};

GamepadButton::GamepadButton(SDL_GamepadButton type) : m_type(type) {}

bool GamepadButton::IsPressing() const {
    return m_last_press && m_is_press;
}

bool GamepadButton::IsReleasing() const {
    return !(m_last_press && m_is_press);
}

bool GamepadButton::IsReleased() const {
    return m_last_press && !m_is_press;
}

bool GamepadButton::IsPressed() const {
    return !m_last_press && m_is_press;
}

void GamepadButton::handleEvent(const SDL_GamepadButtonEvent& event) {
    if (event.button != m_type) {
        return;
    }
    m_last_press = m_is_press;
    m_is_press = event.down;
    m_has_handled_event = true;
}

void GamepadButton::update() {
    if (!m_has_handled_event) {
        m_last_press = m_is_press;
    }
    m_has_handled_event = false;
}

SDL_GamepadButton GamepadButton::GetType() const {
    return m_type;
}

GamepadAxis::GamepadAxis(SDL_GamepadAxis axis) : m_axis(axis) {}

float GamepadAxis::Value() const {
    return m_value;
}

SDL_GamepadAxis GamepadAxis::GetType() const {
    return m_axis;
}

void GamepadAxis::handleEvent(const SDL_GamepadAxisEvent& event) {
    m_value = event.value > 0 ? event.value / 32768.0f : event.value / 32767.0f;
}

Gamepad::Gamepad(SDL_JoystickID id) : m_id(id) {
    for (int i = 0; i < SDL_GAMEPAD_BUTTON_COUNT; i++) {
        m_buttons[i] =
            std::make_unique<GamepadButton>(static_cast<SDL_GamepadButton>(i));
    }
    for (int i = 0; i < SDL_GAMEPAD_AXIS_COUNT; i++) {
        m_axises[i] =
            std::make_unique<GamepadAxis>(static_cast<SDL_GamepadAxis>(i));
    }
}

const GamepadButton& Gamepad::GetButton(SDL_GamepadButton button) const {
    if (button == SDL_GAMEPAD_BUTTON_INVALID) {
        return InvalidButton;
    }
    return *m_buttons[static_cast<std::size_t>(button)];
}

const GamepadAxis& Gamepad::GetAxis(SDL_GamepadAxis axis) const {
    if (axis == SDL_GAMEPAD_AXIS_INVALID) {
        return InvalidAxis;
    }
    return *m_axises[static_cast<std::size_t>(axis)];
}

void Gamepad::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_GAMEPAD_BUTTON_UP ||
        event.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN) {
        m_buttons[event.gbutton.button]->handleEvent(event.gbutton);
    } else if (event.type == SDL_EVENT_GAMEPAD_AXIS_MOTION) {
        m_axises[event.gaxis.axis]->handleEvent(event.gaxis);
    }
}

void Gamepad::update() {
    for (auto& button : m_buttons) {
        button->update();
    }
}

SDL_JoystickID Gamepad::GetID() const {
    return m_id;
}

void GamepadManager::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_GAMEPAD_ADDED) {
        m_gamepads.emplace(event.gdevice.which, event.gdevice.which);
    } else if (event.type == SDL_EVENT_GAMEPAD_REMOVED) {
        const auto id = event.gdevice.which;
        m_gamepads.erase(event.gdevice.which);
    } else if (event.type == SDL_EVENT_GAMEPAD_BUTTON_UP ||
               event.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN ||
               event.type == SDL_EVENT_GAMEPAD_AXIS_MOTION) {
        for (auto& [_, gamepad] : m_gamepads) {
            gamepad.handleEvent(event);
        }
    }
}

void GamepadManager::Update() {
    for (auto& [_, gamepad] : m_gamepads) {
        gamepad.update();
    }
}

const std::unordered_map<SDL_JoystickID, Gamepad>& GamepadManager::GetGamepads()
    const {
    return m_gamepads;
}
