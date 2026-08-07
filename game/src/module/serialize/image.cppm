export module image.serialize;

export import image;

import handle;
import simdjson;

export {
namespace simdjson {
void tag_invoke(serialize_tag, builder::string_builder &builder,
                const Image *payload);

simdjson::error_code tag_invoke(deserialize_tag, ondemand::document &val,
                                Image *&payload);
simdjson::error_code tag_invoke(deserialize_tag, ondemand::value &val,
                                Image *&payload);
void tag_invoke(serialize_tag tag, builder::string_builder &builder,
                const Handle<Image> &payload);

simdjson::error_code tag_invoke(deserialize_tag tag, ondemand::document &val,
                                Handle<Image> &payload);

simdjson::error_code tag_invoke(deserialize_tag tag, ondemand::value &val,
                                Handle<Image> &payload);
}  // namespace simdjson
}
