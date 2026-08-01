module;
export module sprite.manager;

import sprite;

import manager;

export class SpriteManager : public ComponentManager<Sprite> {
public:
    void Update();
};
