module;

#include <tree_sitter/api.h>
export module tool;

import std;

export std::string_view get_node_string(TSNode node,
                                        std::string_view source_code) {
    auto s = ts_node_start_byte(node);
    auto e = ts_node_end_byte(node);
    return source_code.substr(s, e - s);
}

export TSNode find_field(const TSNode& node, std::string_view field_name) {
    static std::unordered_map<std::string_view, TSFieldId> fieldIds;

    TSFieldId id;
    const TSLanguage* language = ts_node_language(node);
    auto iter = fieldIds.find(field_name);
    if (iter == fieldIds.end()) {
        id = ts_language_field_id_for_name(language, field_name.data(),
                                           field_name.size());
        fieldIds.insert({field_name, id});
    } else {
        id = iter->second;
    }
    return ts_node_child_by_field_id(node, id);
}
