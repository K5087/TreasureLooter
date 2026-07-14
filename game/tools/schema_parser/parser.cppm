module;
struct TSNode;
struct TSParser;
struct TSLanguage;
export module parser;

import common;

import std;

extern "C" const TSLanguage* tree_sitter_cpp(void);

std::optional<std::string> parse_include(const TSNode& node,
                                         std::string_view source_code);
std::optional<ClassInfo> parse_class(const TSNode& node,
                                     std::string_view source_code);
std::optional<FieldInfo> parse_field(const TSNode& node,
                                     std::string_view source_code);
std::optional<EnumInfo> parse_enum(const TSNode& node,
                                   std::string_view source_code);

export namespace TS {
class Parser {
public:
    Parser();
    ~Parser();

    std::optional<SchemaInfo> parse_cpp(std::filesystem::path filename);

private:
    void parse_node(SchemaInfo& info, const TSNode& node,
                    std::string_view source_code);

private:
    TSParser* parser;
    const TSLanguage* language;
};
}  // namespace TS
