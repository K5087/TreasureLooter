module;
export module asset;
import entity;
import simdjson;

export {
template <typename T>
class Asset {
public:
    Entity entity;
    T data;
};

namespace simdjson {
template <typename builder_type, typename T>
void tag_invoke(serialize_tag, builder_type& builder, const Asset<T>& payload) {
    builder.start_object();
    builder.template append_key_value<"entity">(payload.entity);
    builder.append_comma();
    builder.template append_key_value<"data">(payload.data);
    builder.end_object();
}

template <typename simdjson_value, typename T>
auto tag_invoke(deserialize_tag, simdjson_value& val, Asset<T>& payload) {
    ondemand::object obj;
    auto error = val.get_object().get(obj);
    if (error) {
        return error;
    }
    if ((error = obj["entity"].get(payload.entity))) {
        return error;
    }
    if ((error = obj["data"].get(payload.data))) {
        return error;
    }
    return simdjson::SUCCESS;
}
}  // namespace simdjson
}
