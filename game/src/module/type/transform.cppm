module;

export module transform:type;

import math;

export struct Transform {
    Pose m_pose;
    Pose m_global_pose;

    Transform() = default;

    explicit Transform(const Pose& pose) : m_pose(pose) {}
};
