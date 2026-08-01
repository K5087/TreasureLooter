export module relationship;

import entity;
import std;

export struct Relationship {
    std::vector<Entity> m_children;
};
