module;
#include <SDL3/SDL.h>
export module finger_touch;

import button;
import math;
import std;

export {
constexpr std::uint8_t MaxFingerNum = 20;

class FingerTouch : public Button {
    friend class Touch;

public:
    virtual bool IsPressing() const override;
    virtual bool IsReleasing() const override;
    virtual bool IsReleased() const override;
    virtual bool IsPressed() const override;

    const Vec2& Position() const;
    const Vec2& Offset() const;

public:
    bool m_is_press = false;
    bool m_last_press = false;
    bool m_has_handled_event = false;
    Vec2 m_position;
    Vec2 m_offset;

    void handleEvent(const SDL_TouchFingerEvent& event);
    void update();
    void postUpdate();
};

class Touch {
public:
    void HandleEvent(const SDL_TouchFingerEvent& event);
    void Update();
    void PostUpdate();

    const std::array<FingerTouch, MaxFingerNum>& GetFingers() const;

private:
    std::array<FingerTouch, MaxFingerNum> m_touches;
};
}
