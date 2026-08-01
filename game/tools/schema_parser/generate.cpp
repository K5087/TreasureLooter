module;
#include <mustache.hpp>
module generate;

import common;

bool is_import(const std::string& name, std::filesystem::path dir) {
    return std::filesystem::exists(dir / (name + ".cppm"));
};

bool has_serialize(const std::string& name, std::filesystem::path dir) {
    return std::filesystem::exists(dir / (name + ".cppm")) or name == "image";
};

namespace lua {
std::string generateClassCode(const ClassInfo& info) {
    auto& field_mustache = MustacheManager::GetInst().lua_field;

    kainjow::mustache::data field_datas{kainjow::mustache::data::type::list};
    for (auto& field : info.fields) {
        kainjow::mustache::data field_data;
        field_data.set("type", field.type);
        field_data.set("name", field.name);
        field_datas << kainjow::mustache::data{
            "field", field_mustache.render(field_data)};
    }

    kainjow::mustache::data class_data;
    class_data.set("name", info.name);
    class_data.set("fields", field_datas);
    auto& class_mustache = MustacheManager::GetInst().lua_class;
    return class_mustache.render(class_data);
}

std::string generateSchemaCode(const SchemaInfo& schema_info) {
    auto& schema_mustache = MustacheManager::GetInst().lua_schema;

    kainjow::mustache::data class_data{kainjow::mustache::data::type::list};
    for (auto& schema : schema_info.classes) {
        class_data << kainjow::mustache::data{"class",
                                              generateClassCode(schema)};
    }

    kainjow::mustache::data enum_data{kainjow::mustache::data::type::list};
    for (auto& enum_info : schema_info.enums) {
        enum_data << kainjow::mustache::data{"enum",
                                             generateEnumCode(enum_info)};
    }
    kainjow::mustache::data schema_data;
    schema_data.set("classes", class_data);
    schema_data.set("enums", enum_data);
    return schema_mustache.render(schema_data);
}

std::string generateEnumCode(const EnumInfo& info) {
    auto& enum_mustache = MustacheManager::GetInst().lua_enum;
    kainjow::mustache::data item_datas{kainjow::mustache::data::type::list};
    for (auto& item : info.items) {
        std::string data = item.name;
        if (item.value) {
            data += " = " + std::to_string(*item.value) + ",";
        }
        item_datas << kainjow::mustache::data{"item", data};
    }

    kainjow::mustache::data enum_data;
    enum_data.set("name", info.name);
    enum_data.set("items", item_datas);
    return enum_mustache.render(enum_data);
}
}  // namespace lua

namespace cpp {

namespace serialize {

std::string generate(const EnumInfo& info) {
    kainjow::mustache::data serialize_data;
    kainjow::mustache::data item_datas{kainjow::mustache::data::type::list};
    kainjow::mustache::data no_zero_item_datas{
        kainjow::mustache::data::type::list};
    for (size_t i = 0; i < info.items.size(); i++) {
        auto& item = info.items[i];
        kainjow::mustache::data item_data;
        item_data.set("name", item.name);
        item_data.set("type", info.name);
        item_data.set("not_first", i != 0);
        item_datas << item_data;
        if (item.value == 0) {
            serialize_data.set("zero_name", item.name);
            serialize_data.set("is_zero", true);
        } else {
            no_zero_item_datas << item_data;
        }
    }
    serialize_data.set("type", info.name);
    serialize_data.set("fields", item_datas);
    serialize_data.set("no_zero_fields", no_zero_item_datas);
    auto& serialize_mustache = MustacheManager::GetInst().cpp_enum_serialize;
    return serialize_mustache.render(serialize_data);
}

std::string generate(const ClassInfo& info) {
    kainjow::mustache::data field_datas{kainjow::mustache::data::type::list};
    for (size_t i = 0; i < info.fields.size(); i++) {
        auto& field = info.fields[i];
        kainjow::mustache::data field_data;
        field_data.set("name", field.name);
        field_data.set("not_end", i != info.fields.size() - 1);
        field_datas << field_data;
    }
    kainjow::mustache::data serialize_data;
    serialize_data.set("type", info.name);
    serialize_data.set("fields", field_datas);
    auto& serialize_mustache = MustacheManager::GetInst().cpp_class_serialize;
    return serialize_mustache.render(serialize_data);
}

std::string generate(const SchemaInfo& schema_info) {
    kainjow::mustache::data serialize_datas{
        kainjow::mustache::data::type::list};
    for (auto& schema : schema_info.classes) {
        if (schema.fields.empty()) {
            continue;
        }
        serialize_datas << kainjow::mustache::data{"serialize",
                                                   generate(schema)};
    }
    for (auto& schema : schema_info.enums) {
        serialize_datas << kainjow::mustache::data{"serialize",
                                                   generate(schema)};
    }

    kainjow::mustache::data import_datas{kainjow::mustache::data::type::list};
    for (auto& include : schema_info.includes) {
        if (has_serialize(include, schema_info.filename.parent_path())) {
            import_datas << kainjow::mustache::data{"name", include};
        }
    }

    auto& schema_mustache = MustacheManager::GetInst().cpp_schema_serialize;
    kainjow::mustache::data schema_data;
    schema_data.set("serializes", serialize_datas);
    schema_data.set("name", schema_info.filename.stem().string());
    schema_data.set("imports", import_datas);
    schema_data.set("has_enum", schema_info.enums.size() > 0);
    return schema_mustache.render(schema_data);
}

}  // namespace serialize

namespace display {

std::string generate(const EnumInfo& info) {
    kainjow::mustache::data display_data;
    kainjow::mustache::data item_datas{kainjow::mustache::data::type::list};
    for (size_t i = 0; i < info.items.size(); i++) {
        auto& item = info.items[i];
        kainjow::mustache::data item_data;
        item_data.set("item", item.name);
        item_data.set("type", info.name);
        if (item.value) {
            item_data.set("idx", std::to_string(*item.value));
        }
        item_datas << item_data;
    }
    display_data.set("type", info.name);
    display_data.set("items", item_datas);
    auto& serialize_mustache = MustacheManager::GetInst().cpp_enum_display;
    return serialize_mustache.render(display_data);
}

std::string generate(const ClassInfo& info) {
    kainjow::mustache::data field_datas{kainjow::mustache::data::type::list};
    for (size_t i = 0; i < info.fields.size(); i++) {
        auto& field = info.fields[i];
        kainjow::mustache::data field_data;
        field_data.set("field", field.name);
        field_datas << field_data;
    }
    kainjow::mustache::data display_data;
    display_data.set("type", info.name);
    display_data.set("fields", field_datas);
    auto& display_mustache = MustacheManager::GetInst().cpp_class_display;
    return display_mustache.render(display_data);
}

std::string generate(const SchemaInfo& schema_info) {
    kainjow::mustache::data display_datas{kainjow::mustache::data::type::list};
    for (auto& schema : schema_info.classes) {
        if (schema.fields.empty()) {
            continue;
        }
        display_datas << kainjow::mustache::data{"display", generate(schema)};
    }

    for (auto& schema : schema_info.enums) {
        display_datas << kainjow::mustache::data{"display", generate(schema)};
    }

    kainjow::mustache::data import_datas{kainjow::mustache::data::type::list};
    for (auto& include : schema_info.includes) {
        if (is_import(include, schema_info.filename.parent_path())) {
            import_datas << kainjow::mustache::data{"name", include};
        }
    }
    auto& schema_mustache = MustacheManager::GetInst().cpp_schema_display;
    kainjow::mustache::data schema_data;

    schema_data.set("name", schema_info.filename.stem().string());
    schema_data.set("has_enum", schema_info.enums.size() > 0);
    schema_data.set("imports", import_datas);
    // math display impl in instance_display
    if (schema_info.filename.stem().string() != "math") {
        schema_data.set("displays", display_datas);
    }
    return schema_mustache.render(schema_data);
}
}  // namespace display
}  // namespace cpp
