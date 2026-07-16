module;

export module prefab:type;

import entity;
import sprite;
import transform;
import relationship;

export class Prefab {
public:
    Sprite m_sprite;
    Transform m_transform;
    Relationship m_relation;
};
