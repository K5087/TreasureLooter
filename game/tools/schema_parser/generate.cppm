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
namespace serialize {
std::string generate(const EnumInfo& info);
std::string generate(const ClassInfo& info);
std::string generate(const SchemaInfo& info);

}  // namespace serialize

namespace display {
std::string generate(const EnumInfo& info);
std::string generate(const ClassInfo& info);
std::string generate(const SchemaInfo& info);
}  // namespace display

}  // namespace cpp
}
