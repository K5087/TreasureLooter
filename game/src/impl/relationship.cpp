module;
#include <log.hpp>
module relationship.manager;

import log;
import entity;
import context;

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
    Transform *root_transform = transform_manager->Get(m_root);
    if (!root_transform) {
        LOGE(
            "[Component][RelationshipManager] root eneity don't has transform");
        return;
    }

    root_transform->UpdateMat(nullptr);
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
    transform->UpdateMat(&parent);
    Relationship *relationship = Get(child);
    if (!relationship) {
        return;
    }
    for (auto &c : relationship->m_children) {
        updatePoseRecursive(*transform, c);
    }
}
