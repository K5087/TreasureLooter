module;
#include <mustache.hpp>
module common;

import std;

MustacheManager& MustacheManager::GetInst() {
    static MustacheManager instance;
    return instance;
}

MustacheManager::MustacheManager()
    : lua_class(
          readMustache("tools/schema_parser/template/lua/class.mustache")),
      lua_field(
          readMustache("tools/schema_parser/template/lua/field.mustache")),
      lua_schema(
          readMustache("tools/schema_parser/template/lua/schema.mustache")),
      lua_enum(readMustache("tools/schema_parser/template/lua/enum.mustache")),
      cpp_class_serialize(readMustache(
          "tools/schema_parser/template/cpp/serialize/class.mustache")),
      cpp_enum_serialize(readMustache(
          "tools/schema_parser/template/cpp/serialize/enum.mustache")),
      cpp_schema_serialize(readMustache(
          "tools/schema_parser/template/cpp/serialize/schema.mustache")),
      cpp_enum_display(readMustache(
          "tools/schema_parser/template/cpp/display/enum.mustache")),
      cpp_class_display(readMustache(
          "tools/schema_parser/template/cpp/display/class.mustache")),
      cpp_schema_display(readMustache(
          "tools/schema_parser/template/cpp/display/schema.mustache"))

{}

kainjow::mustache::mustache MustacheManager::readMustache(
    const std::filesystem::path& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Can't find mustache file  " << path << std::endl;
        return {};
    }

    auto content = std::string(std::istreambuf_iterator(file), {});
    return kainjow::mustache::mustache(content);
}
