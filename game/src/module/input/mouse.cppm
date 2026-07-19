module;
#include <SDL3/SDL.h>
export module mouse;

import button;
import math;
import std;

export {
enum class MouseButtonType {
    Left = SDL_BUTTON_LEFT,
    Right = SDL_BUTTON_RIGHT,
    Middle = SDL_BUTTON_MIDDLE,
    X1 = SDL_BUTTON_X1,
    X2 = SDL_BUTTON_X2
};

class MouseButton : public Button {
    friend class Mouse;

public:
    explicit MouseButton(MouseButtonType type);

    virtual bool IsPressing() const override;
    virtual bool IsReleasing() const override;
    virtual bool IsReleased() const override;
    virtual bool IsPressed() const override;

private:
    MouseButtonType m_type;
    bool m_is_press = false;
    bool m_last_press = false;
    bool m_has_handled_event = false;

    void handleEvent(const SDL_MouseButtonEvent& event);
    void update();
};

class Mouse {
public:
    Mouse();
    void HandleEvent(const SDL_Event& event);
    void Update();
    void PostUpdate();

    const MouseButton& Get(MouseButtonType type) const;

private:
    std::array<MouseButton, 5> m_buttons;
    Vec2 m_cur_position;
    Vec2 m_cur_offset;
};
}
