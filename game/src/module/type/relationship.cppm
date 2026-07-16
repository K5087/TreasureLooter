export module relationship:type;
import std;
import entity;

export struct Relationship {
    std::vector<Entity> m_children;
};
