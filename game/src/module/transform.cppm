module;
export module transform;

import math;
import manager;

export struct Transform {
    Pose m_pose;
    Pose m_global_pose;

    Transform() = default;

    explicit Transform(const Pose& pose) : m_pose(pose) {}
};

export class TransformManager : public ComponentManager<Transform> {};
