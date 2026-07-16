module;
export module sprite;

export import :type;
export import :serialize;

import manager;

export class SpriteManager : public ComponentManager<Sprite> {
public:
    void Update();
};
