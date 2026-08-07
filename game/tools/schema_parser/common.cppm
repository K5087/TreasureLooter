module;
#include <mustache.hpp>
export module common;

import std;

export {
struct FieldInfo {
    std::string type;
    std::string name;
    std::optional<std::string> value;
};

struct ClassInfo {
    std::string name;
    std::vector<FieldInfo> fields;
};

struct EnumInfo {
    struct Item {
        std::string name;
        std::optional<std::string> value;
    };

    std::string name;
    std::vector<Item> items;
};

struct SchemaInfo {
    std::string name;
    std::filesystem::path filename;

    std::vector<std::string> includes;
    std::vector<ClassInfo> classes;
    std::vector<EnumInfo> enums;
};

struct SchemaManager {
    std::vector<SchemaInfo> infos;
};

struct MustacheManager {
    kainjow::mustache::mustache lua_class;
    kainjow::mustache::mustache lua_field;
    kainjow::mustache::mustache lua_schema;
    kainjow::mustache::mustache lua_enum;
    kainjow::mustache::mustache cpp_class_serialize;
    kainjow::mustache::mustache cpp_enum_serialize;
    kainjow::mustache::mustache cpp_schema_serialize;
    kainjow::mustache::mustache cpp_enum_display;
    kainjow::mustache::mustache cpp_class_display;
    kainjow::mustache::mustache cpp_schema_display;

    static MustacheManager& GetInst();

private:
    MustacheManager();

    kainjow::mustache::mustache readMustache(const std::filesystem::path& path);
};
}
