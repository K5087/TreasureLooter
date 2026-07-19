module;
#include <SDL3/SDL.h>
module keyboard;

KeyboardButton::KeyboardButton(SDL_Keycode key) : m_key(key) {}

bool KeyboardButton::IsPressing() const {
    return m_last_press && m_is_press;
}

bool KeyboardButton::IsReleasing() const {
    return !(m_last_press && m_is_press);
}

bool KeyboardButton::IsReleased() const {
    return m_last_press && !m_is_press;
}

bool KeyboardButton::IsPressed() const {
    return !m_last_press && m_is_press;
}

void KeyboardButton::handleEvent(const SDL_KeyboardEvent& event) {
    if (event.key != m_key) {
        return;
    }
    m_last_press = m_is_press;
    if (event.type == SDL_EVENT_KEY_DOWN) {
        m_is_press = true;
    } else {
        m_is_press = false;
    }
    m_has_handled_event = true;
}

void KeyboardButton::update() {
    if (!m_has_handled_event) {
        m_last_press = m_is_press;
    }
    m_has_handled_event = false;
}

void Keyboard::HandleEvent(const SDL_KeyboardEvent& event) {
    if (auto it = m_buttons.find(event.key); it != m_buttons.end()) {
        it->second.handleEvent(event);
    } else {
        auto button = m_buttons.emplace(event.key, KeyboardButton(event.key));
        button.first->second.handleEvent(event);
    }
}

void Keyboard::Update() {
    for (auto& [_, button] : m_buttons) {
        button.update();
    }
}

const KeyboardButton& Keyboard::Get(SDL_Keycode key) {
    return m_buttons.try_emplace(key, key).first->second;
}
