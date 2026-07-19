module;
#include <SDL3/SDL.h>
export module keyboard;

import std;
import button;

export {
class KeyboardButton : public Button {
public:
    friend class Keyboard;
    explicit KeyboardButton(SDL_Keycode key);

    virtual bool IsPressing() const override;
    virtual bool IsReleasing() const override;
    virtual bool IsReleased() const override;
    virtual bool IsPressed() const override;

private:
    SDL_Keycode m_key;
    bool m_is_press = false;
    bool m_last_press = false;
    bool m_has_handled_event = false;

    void handleEvent(const SDL_KeyboardEvent& event);
    void update();
};

class Keyboard {
public:
    void HandleEvent(const SDL_KeyboardEvent& event);
    void Update();

    const KeyboardButton& Get(SDL_Keycode key);

private:
    std::unordered_map<SDL_Keycode, KeyboardButton> m_buttons;
};
}
