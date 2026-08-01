module;
export module relationship.manager;

import relationship;

import entity;
import manager;
import math;

import std;

export class RelationshipManager : public ComponentManager<Relationship> {
public:
    RelationshipManager(Entity entity);
    void Update();

private:
    Entity m_root;

    void updatePoseRecursive(const Transform &parent, Entity child);
};
