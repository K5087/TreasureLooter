export module tilemap.serialize;
export import tilemap;

import simdjson;
import handle;

export {
namespace simdjson {
void tag_invoke(serialize_tag tag, builder::string_builder &builder,
                const Handle<Tilemap> &payload);
simdjson::error_code tag_invoke(deserialize_tag, ondemand::document &val,
                                Handle<Tilemap> &payload);

simdjson::error_code tag_invoke(deserialize_tag, ondemand::value &val,
                                Handle<Tilemap> &payload);

void tag_invoke(serialize_tag, builder::string_builder &builder,
                const Tilemap *payload);

simdjson::error_code tag_invoke(deserialize_tag, ondemand::document &val,
                                const Tilemap *payload);

simdjson::error_code tag_invoke(deserialize_tag, ondemand::value &val,
                                Tilemap *&payload);
}  // namespace simdjson
}
