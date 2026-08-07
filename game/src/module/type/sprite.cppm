module;

export module sprite;

import flag;
import image;
import math;
import renderer;
import flip;
import handle;

export struct Sprite {
    Handle<Image> m_image{};
    Region m_region;
    Vec2 m_size;
    Flags<Flip> m_flip = Flip::None;

    operator bool() const { return m_image; }
};
