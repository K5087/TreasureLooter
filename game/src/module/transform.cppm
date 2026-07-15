module;
export module transform;

export import :type;
export import :serialize;

import manager;

export class TransformManager : public ComponentManager<Transform> {};
