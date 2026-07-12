module;
#include <mustache.hpp>
module generate;

import common;

std::string generateClassCode(const ClassInfo& info) {
    auto& field_mustache = MustacheManager::GetInst().field_mustache;

    kainjow::mustache::data field_datas{kainjow::mustache::data::type::list};
    for (auto& field : info.fields) {
        kainjow::mustache::data field_data;
        field_data.set("type", field.type);
        field_data.set("name", field.name);
        field_datas << kainjow::mustache::data{
            "fields", field_mustache.render(field_data)};
    }

    kainjow::mustache::data class_data;
    class_data.set("name", info.name);
    class_data.set("fields", field_datas);
    auto& class_mustache = MustacheManager::GetInst().class_mustache;
    return class_mustache.render(class_data);
}

std::string generateSchemaCode(const SchemaInfo& schema_info) {
    auto& schema_mustache = MustacheManager::GetInst().schema_mustache;

    kainjow::mustache::data class_data{kainjow::mustache::data::type::list};
    for (auto& schema : schema_info.classes) {
        class_data << kainjow::mustache::data{"class",
                                              generateClassCode(schema)};
    }
    kainjow::mustache::data schema_data;
    schema_data.set("class", class_data);
    return schema_mustache.render(schema_data);
}
