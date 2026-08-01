module;

export module prefab;

import entity;
import sprite;
import math;
import relationship;

import std;

export class Prefab {
public:
    std::optional<Sprite> m_sprite;
    std::optional<Transform> m_transform;
    std::optional<Relationship> m_relation;
};

export class EntityInstance {
public:
    Entity m_entity;
    Prefab m_data;
};
