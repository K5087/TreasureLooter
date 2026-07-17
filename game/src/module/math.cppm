module;
export module math;

export import :type;
export import :serialize;

import simdjson;

export namespace simdjson {
template <typename builder_type>
void tag_invoke(serialize_tag, builder_type& builder, const Degrees& payload) {
    builder.append(payload.Value());
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value& val, Degrees& payload) {
    double value;
    auto error = val.get_double().get(value);
    if (error) {
        return error;
    }
    payload = value;

    return simdjson::SUCCESS;
}

template <typename builder_type>
void tag_invoke(serialize_tag, builder_type& builder, const Radians& payload) {
    builder.append(payload.Value());
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value& val, Radians& payload) {
    double value;
    auto error = val.get_double().get(value);
    if (error) {
        return error;
    }
    payload = value;

    return simdjson::SUCCESS;
}
}  // namespace simdjson
