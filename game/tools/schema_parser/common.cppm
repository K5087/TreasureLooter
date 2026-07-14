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
        std::optional<int> value;
    };

    std::string name;
    std::vector<Item> items;
};

struct SchemaInfo {
    std::vector<std::string> includes;
    std::filesystem::path filename;
    std::vector<ClassInfo> classes;
    std::vector<EnumInfo> enums;
};

struct SchemaManager {
    std::vector<SchemaInfo> infos;
};

struct MustacheManager {
    kainjow::mustache::mustache class_mustache;
    kainjow::mustache::mustache field_mustache;
    kainjow::mustache::mustache schema_mustache;
    kainjow::mustache::mustache enum_mustache;

    static MustacheManager& GetInst();

private:
    MustacheManager();

    kainjow::mustache::mustache readMustache(const std::filesystem::path& path);
};
}
