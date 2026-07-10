module;
export module relationship;

import entity;
import manager;
import transform;

import std;

export struct Relationship {
    std::vector<Entity> m_children;
};

export class RelationshipManager : public ComponentManager<Relationship> {
public:
    RelationshipManager(Entity entity);
    void Update();

private:
    Entity m_root;

    void updatePoseRecursive(const Transform &parent, Entity child);
};
