module;
#include <simdjson.h>
export module simdjson;

export namespace simdjson {
using ::simdjson::deserialize_tag;
using ::simdjson::error_code;
using ::simdjson::serialize_tag;

using ::simdjson::pad;
using ::simdjson::to_json;

using ::simdjson::error_message;

namespace ondemand = SIMDJSON_BUILTIN_IMPLEMENTATION::ondemand;

namespace SIMDJSON_BUILTIN_IMPLEMENTATION {
namespace ondemand {
using ::simdjson::ondemand::object;
using ::simdjson::ondemand::parser;

using ::simdjson::ondemand::document;
}  // namespace ondemand
}  // namespace SIMDJSON_BUILTIN_IMPLEMENTATION
}  // namespace simdjson
