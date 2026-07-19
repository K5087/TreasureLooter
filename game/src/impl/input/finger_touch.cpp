module;
#include <SDL3/SDL.h>
#include <log.hpp>
module finger_touch;

import log;

bool FingerTouch::IsPressing() const {
    return m_last_press && m_is_press;
}

bool FingerTouch::IsReleasing() const {
    return !(m_last_press && m_is_press);
}

bool FingerTouch::IsReleased() const {
    return m_last_press && !m_is_press;
}

bool FingerTouch::IsPressed() const {
    return !m_last_press && m_is_press;
}
const Vec2& FingerTouch::Position()const {
    return m_position;
}
const Vec2& FingerTouch::Offset()const{
return m_offset;
}

void FingerTouch::handleEvent(const SDL_TouchFingerEvent& event) {
    m_position.x = event.x;
    m_position.y = event.y;
    m_offset.x = event.dx;
    m_offset.y = event.dy;

    if (event.type == SDL_EVENT_FINGER_DOWN ||
        event.type == SDL_EVENT_FINGER_UP) {
        m_last_press = m_is_press;
        if (event.type == SDL_EVENT_FINGER_DOWN) {
            m_is_press = true;
        } else {
            m_is_press = false;
        }
        m_has_handled_event = true;
    }
}

void FingerTouch::update() {
    if (!m_has_handled_event) {
        m_last_press = m_is_press;
    }
    m_has_handled_event = false;
}

void FingerTouch::postUpdate() {
    m_offset = {};
}

void Touch::HandleEvent(const SDL_TouchFingerEvent& event) {
    if (event.fingerID >= m_touches.size()) {
        LOGW("finger id out of range. ID = {}, max touch size = {}",
             event.fingerID, m_touches.size());
 

    }
    m_touches[event.fingerID].handleEvent(event);
}
void Touch::Update() {
for(auto& touch:m_touches) {

        touch.update();
    }
}
void Touch::PostUpdate() {
    for (auto& touch : m_touches) {
        touch.postUpdate();
    }
}

const std::array<FingerTouch,MaxFingerNum>& Touch::GetFingers() const {
    return m_touches;
}
