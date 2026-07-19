module;
#include <SDL3/SDL.h>
module mouse;

MouseButton::MouseButton(MouseButtonType type) : m_type(type) {}

bool MouseButton::IsPressing() const {
    return m_last_press && m_is_press;
}

bool MouseButton::IsReleasing() const {
    return !(m_last_press && m_is_press);
}

bool MouseButton::IsReleased() const {
    return m_last_press && !m_is_press;
}

bool MouseButton::IsPressed() const {
    return !m_last_press && m_is_press;
}

void MouseButton::handleEvent(const SDL_MouseButtonEvent& event) {
    if (event.type != static_cast<uint8_t>(m_type)) {
        return;
    }
    m_last_press = m_is_press;
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        m_is_press = true;
    } else {
        m_is_press = false;
    }
    m_has_handled_event = true;
}

Mouse::Mouse()
    : m_buttons{MouseButton{MouseButtonType::Left},
                MouseButton{MouseButtonType::Middle},
                MouseButton{MouseButtonType::Right},
                MouseButton{MouseButtonType::X1},
                MouseButton{MouseButtonType::X2}} {}

void MouseButton::update() {
    if (!m_has_handled_event) {
        m_last_press = m_is_press;
    }
    m_has_handled_event = false;
}

void Mouse::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP ||
        event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        for (auto& button : m_buttons) {
            button.handleEvent(event.button);
        }
    } else if (event.type == SDL_EVENT_MOUSE_MOTION) {
        m_cur_position.x = event.motion.x;
        m_cur_position.y = event.motion.y;
        m_cur_offset.y = event.motion.xrel;
        m_cur_offset.y = event.motion.yrel;
    }
}

void Mouse::Update() {
    for (auto& button : m_buttons) {
        button.update();
    }
}

void Mouse::PostUpdate() {
    m_cur_offset = Vec2{};
}

const MouseButton& Mouse::Get(MouseButtonType type) const {
    return m_buttons[static_cast<uint8_t>(type)];
}
