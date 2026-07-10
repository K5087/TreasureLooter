module;
export module sprite;

import flag;
import image;
import math;
import renderer;
import manager;

export struct Sprite {
    Image* m_image{};
    Region m_region;
    Vec2 m_size;
    Flags<Flip> m_flip = Flip::None;

    operator bool() const { return m_image; }
};

export class SpriteManager : public ComponentManager<Sprite> {
public:
    void Update();
};
