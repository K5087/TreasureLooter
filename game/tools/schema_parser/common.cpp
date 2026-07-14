module;
#include <mustache.hpp>
module common;

import std;

MustacheManager& MustacheManager::GetInst() {
    static MustacheManager instance;
    return instance;
}

MustacheManager::MustacheManager()
    : class_mustache(
          readMustache("tools/schema_parser/template/class.mustache")),
      field_mustache(
          readMustache("tools/schema_parser/template/field.mustache")),
      schema_mustache(
          readMustache("tools/schema_parser/template/schema.mustache")),
      enum_mustache(readMustache("tools/schema_parser/template/enum.mustache"))

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
