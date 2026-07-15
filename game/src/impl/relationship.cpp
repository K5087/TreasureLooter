module;
module relationship;

import entity;
import transform;
import context;
import log;

RelationshipManager::RelationshipManager(Entity entity) : m_root(entity) {
    RegisterEntity(entity);
}

void RelationshipManager::Update() {
    auto relationship = Get(m_root);
    if (!relationship) {
        // LOGE("[Component][RelationShipManager] don't has root entity");
        return;
    }
    auto &transform_manager = Context::GetInst().m_transform_manager;
    const Transform *root_transform = transform_manager->Get(m_root);
    for (auto &child : relationship->m_children) {
        updatePoseRecursive(*root_transform, child);
    }
}

void RelationshipManager::updatePoseRecursive(const Transform &parent,
                                              Entity child) {
    auto &transform_manager = Context::GetInst().m_transform_manager;
    Transform *transform = transform_manager->Get(child);
    if (!transform) {
        LOGE("[Component][RelationShipManager] entity {} doesn't has transform",
             child);
        return;
    }
    transform->m_global_pose = parent.m_global_pose * transform->m_pose;
    Relationship *relationship = Get(child);
    if (!relationship) {
        return;
    }
    for (auto &c : relationship->m_children) {
        updatePoseRecursive(*transform, c);
    }
}
