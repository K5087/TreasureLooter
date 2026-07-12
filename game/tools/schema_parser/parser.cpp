module;
#include <tree_sitter/api.h>
module parser;

import tool;
import std;

#define get_symbol(language, name) \
    ts_language_symbol_for_name(language, name, std::strlen(name), true);

bool is_class(const TSNode& node) {
    // for cache
    const TSLanguage* language = ts_node_language(node);
    static std::array class_names = {"class_specifier", "struct_specifier"};
    static std::unordered_set<TSSymbol> class_symbols;
    for (auto name : class_names) {
        TSSymbol symbol = ts_language_symbol_for_name(language, name,
                                                      std::strlen(name), true);
        class_symbols.insert(symbol);
    }

    // impl
    TSSymbol symbol = ts_node_symbol(node);
    return class_symbols.contains(symbol);
}

std::vector<std::string> find_includes(const TSNode& node,
                                       std::string_view source_code) {
    const TSLanguage* language = ts_node_language(node);
    static TSSymbol include_symbol = get_symbol(language, "preproc_include");
    static TSSymbol import_symbol = get_symbol(language, "module_declaration");

    std::vector<std::string> includes;
    for (uint32_t i = 0; i < ts_node_named_child_count(node); i++) {
        TSNode child = ts_node_named_child(node, i);
        TSSymbol child_symbol = ts_node_symbol(child);
        if (child_symbol == include_symbol) {
            TSNode path = find_field(child, "path");
            includes.emplace_back(get_node_string(path, source_code));
        } else if (child_symbol == import_symbol) {
            TSNode name = find_field(child, "name");
            includes.emplace_back(get_node_string(name, source_code));
        }
    }

    return includes;
}

std::vector<ClassInfo> find_class(const TSNode& node,
                                  std::string_view source_code) {
    std::vector<ClassInfo> class_infos;
    for (uint32_t i = 0; i < ts_node_named_child_count(node); i++) {
        TSNode child = ts_node_named_child(node, i);
        if (is_class(child)) {
            ClassInfo class_info;
            TSNode type = find_field(child, "name");
            class_info.name = get_node_string(type, source_code);
            TSNode body = find_field(child, "body");
            if (ts_node_is_null(body) or ts_node_named_child_count(body) == 0) {
                continue;
            }
            class_info.fields = get_field(body, source_code);
            class_infos.push_back(class_info);
        } else {
            std::vector<ClassInfo> child_class = find_class(child, source_code);
            if (!child_class.empty()) {
                class_infos.insert(class_infos.end(), child_class.begin(),
                                   child_class.end());
            }
        }
    }
    return class_infos;
}

std::vector<FieldInfo> get_field(const TSNode& node,
                                 std::string_view source_code) {
    const TSLanguage* language = ts_node_language(node);

    static TSSymbol field_symbol = get_symbol(language, "field_identifier");
    static TSSymbol ptr_symbol = get_symbol(language, "pointer_declarator");
    static TSSymbol declaration_symbol =
        get_symbol(language, "field_declaration");

    std::vector<FieldInfo> field_infos;
    for (uint32_t i = 0; i < ts_node_named_child_count(node); i++) {
        TSNode child = ts_node_named_child(node, i);
        if (ts_node_symbol(child) != declaration_symbol) {
            continue;
        }

        TSNode declarator = find_field(child, "declarator");
        if (ts_node_is_null(declarator)) {
            continue;
        }
        TSSymbol node_symbol = ts_node_symbol(declarator);
        if (node_symbol == ptr_symbol) {
            declarator = find_field(declarator, "declarator");
            if (ts_node_is_null(declarator)) {
                continue;
            }
            node_symbol = ts_node_symbol(declarator);
        }

        if (node_symbol == field_symbol) {
            FieldInfo info;
            info.name = get_node_string(declarator, source_code);
            TSNode type = find_field(child, "type");
            info.type = get_node_string(type, source_code);
            TSNode value = find_field(child, "default_value");
            if (!ts_node_is_null(value)) {
                info.value = get_node_string(value, source_code);
            }

            field_infos.push_back(info);
        }
    }
    return field_infos;
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
    if (!tree) {
        std::cerr << "Failed to parse cpp\n";
        return std::nullopt;
    }

    SchemaInfo schema_info;
    schema_info.filename = filename;
    // parse impl
    TSNode root_node = ts_tree_root_node(tree);
    std::vector<std::string> includes = find_includes(root_node, source_code);
    std::vector<ClassInfo> class_infos = find_class(root_node, source_code);
    schema_info.classes = class_infos;

    ts_tree_delete(tree);
    return schema_info;
}

}  // namespace TS
