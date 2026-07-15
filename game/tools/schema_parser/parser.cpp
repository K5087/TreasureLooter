module;
#include <tree_sitter/api.h>
module parser;

import tool;
import std;

#define get_symbol(language, name) \
    ts_language_symbol_for_name(language, name, std::strlen(name), true);

static const TSLanguage* language = tree_sitter_cpp();
static TSSymbol import_symbol = get_symbol(language, "module_declaration");
static TSSymbol include_symbol = get_symbol(language, "preproc_include");
static TSSymbol class_symbol = get_symbol(language, "class_specifier");
static TSSymbol struct_symbol = get_symbol(language, "struct_specifier");
static TSSymbol enum_symbol = get_symbol(language, "enum_specifier");
static TSSymbol declaration_symbol = get_symbol(language, "field_declaration");
static TSSymbol field_symbol = get_symbol(language, "field_identifier");
static TSSymbol access_symbol = get_symbol(language, "access_specifier");
static TSSymbol union_symbol = get_symbol(language, "union_specifier");

std::optional<std::string> parse_include(const TSNode& node,
                                         std::string_view source_code) {
    TSNode path = find_field(node, "path");
    return std::string(get_node_string(path, source_code));
}

std::optional<std::string> parse_import(const TSNode& node,
                                        std::string_view source_code) {
    TSNode name = find_field(node, "name");
    return std::string(get_node_string(name, source_code));
}

std::optional<ClassInfo> parse_class(const TSNode& node,
                                     std::string_view source_code) {
    ClassInfo info;
    TSNode type = find_field(node, "name");
    info.name = get_node_string(type, source_code);
    TSNode body = find_field(node, "body");
    if (ts_node_is_null(body) or ts_node_named_child_count(body) == 0) {
        return std::nullopt;
    }
    static bool access = true;
    access = true;
    for (uint32_t i = 0; i < ts_node_named_child_count(body); i++) {
        TSNode child = ts_node_named_child(body, i);
        TSSymbol symbol = ts_node_symbol(child);
        if (symbol == access_symbol) {
            if (get_node_string(child, source_code) == "private") {
                access = false;
            } else {
                access = true;
            }
        }
        if (!access) {
            continue;
        }
        if (symbol == declaration_symbol) {
            auto field_info = parse_field(child, source_code);
            if (field_info) {
                info.fields.push_back(*field_info);
            }
        }
    }
    return info;
}

std::optional<FieldInfo> parse_field(const TSNode& node,
                                     std::string_view source_code) {
    TSNode impl;
    TSNode type = find_field(node, "type");
    if (ts_node_symbol(type) == union_symbol) {
        TSNode body = find_field(type, "body");
        auto count = ts_node_named_child_count(body);
        if (count == 0) {
            return std::nullopt;
        }
        impl = ts_node_named_child(body, 0);
    }
    TSNode declarator = find_field(impl, "declarator");
    if (ts_node_is_null(declarator)) {
        return std::nullopt;
    }

    TSSymbol node_symbol = ts_node_symbol(declarator);
    static TSSymbol ptr_symbol = get_symbol(language, "pointer_declarator");

    if (node_symbol == ptr_symbol) {
        declarator = find_field(declarator, "declarator");
        if (ts_node_is_null(declarator)) {
            return std::nullopt;
        }
        node_symbol = ts_node_symbol(declarator);
    }

    if (node_symbol == field_symbol) {
        FieldInfo info;
        TSNode type = find_field(impl, "type");
        info.type = get_node_string(type, source_code);
        info.name = get_node_string(declarator, source_code);
        TSNode value = find_field(node, "default_value");
        if (!ts_node_is_null(value)) {
            info.value = get_node_string(value, source_code);
        }

        return info;
    }
    return std::nullopt;
}

std::optional<EnumInfo> parse_enum(const TSNode& node,
                                   std::string_view source_code) {
    EnumInfo info;

    TSNode name = find_field(node, "name");
    TSNode body = find_field(node, "body");
    if (ts_node_is_null(body) or ts_node_named_child_count(body) == 0) {
        return std::nullopt;
    }

    static TSSymbol enumerator_symbol = get_symbol(language, "enumerator");
    for (uint32_t i = 0; i < ts_node_named_child_count(body); i++) {
        TSNode child = ts_node_named_child(body, i);

        if (ts_node_symbol(child) == enumerator_symbol) {
            EnumInfo::Item item;

            TSNode item_name = find_field(child, "name");
            TSNode item_value = find_field(child, "value");
            item.name = get_node_string(item_name, source_code);
            if (!ts_node_is_null(item_value)) {
                item.value = std::stoi(
                    std::string(get_node_string(item_value, source_code)));
            }

            info.items.push_back(item);
        }
    }

    info.name = get_node_string(name, source_code);
    return info;
}

namespace TS {

Parser::Parser() : parser(ts_parser_new()), language(tree_sitter_cpp()) {
    ts_parser_set_language(parser, language);
}

Parser::~Parser() {
    ts_parser_delete(parser);
}

std::optional<SchemaInfo> Parser::parse_cpp(std::filesystem::path filename) {
    std::cout << "parsing " << filename << std::endl;

    // read file
    std::ifstream file(filename);
    if (file.fail()) {
        std::cerr << "Failed to open fileu: " << filename << '\n';
        return std::nullopt;
    }
    std::string source_code(std::istreambuf_iterator<char>(file), {});

    // generate ast
    TSTree* tree = ts_parser_parse_string(parser, nullptr, source_code.c_str(),
                                          source_code.size());

    TSNode root_node = ts_tree_root_node(tree);
    if (!tree) {
        std::cerr << "Failed to parse cpp\n";
        return std::nullopt;
    }

    SchemaInfo schema_info;
    schema_info.filename = filename;

    // parse impl
    parse_node(schema_info, root_node, source_code);

    ts_tree_delete(tree);
    return schema_info;
}

void Parser::parse_node(SchemaInfo& info, const TSNode& node,
                        std::string_view source_code) {
    for (uint32_t i = 0; i < ts_node_named_child_count(node); i++) {
        TSNode child = ts_node_named_child(node, i);
        TSSymbol child_symbol = ts_node_symbol(child);
        if (child_symbol == include_symbol) {
            auto include = parse_include(child, source_code);
            if (include) {
                info.includes.push_back(*include);
            }
        } else if (child_symbol == import_symbol) {
            auto import = parse_import(child, source_code);
            if (import) {
                info.includes.push_back(*import);
            }
        } else if (child_symbol == class_symbol or
                   child_symbol == struct_symbol) {
            auto class_info = parse_class(child, source_code);
            if (class_info) {
                info.classes.push_back(*class_info);
            }
        } else if (child_symbol == enum_symbol) {
            auto enum_info = parse_enum(child, source_code);
            if (enum_info) {
                info.enums.push_back(*enum_info);
            }
        } else {
            parse_node(info, child, source_code);
        }
    }
}
}  // namespace TS
