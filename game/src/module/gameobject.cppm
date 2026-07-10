module;
export module gameobject;

import sprite;
import math;

import std;

export struct GameObject {
    Pose m_pose;
    Sprite m_sprite;

    std ::vector<GameObject> m_children;

    const Pose& GetGlobalPose() const { return m_global_pose; }

private:
    Pose m_global_pose;
};
