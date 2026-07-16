module;
export module generate;
import common;
import std;

export {
namespace lua {
std::string generateClassCode(const ClassInfo& info);
std::string generateSchemaCode(const SchemaInfo& schema_info);
std::string generateEnumCode(const EnumInfo& info);
}  // namespace lua

namespace cpp {

std::string generateSerializeCode(const EnumInfo& info);
std::string generateSerializeCode(const ClassInfo& info);
std::string generateSchemaCode(const SchemaInfo& schema_info);
}  // namespace cpp
}
