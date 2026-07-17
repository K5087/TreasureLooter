module;

export module sprite:type;

import flag;
import image;
import math;
import renderer;
export import flip;

export struct Sprite {
    Image* m_image{};
    Region m_region;
    Vec2 m_size;
    Flags<Flip> m_flip = Flip::None;

    operator bool() const { return m_image; }
};
