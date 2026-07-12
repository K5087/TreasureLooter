module;
struct TSNode;
struct TSParser;
struct TSLanguage;
export module parser;

import common;

import std;

extern "C" const TSLanguage* tree_sitter_cpp(void);

bool is_class(const TSNode& node);

std::vector<std::string> find_includes(const TSNode& node,
                                       std::string_view source_code);
std::vector<ClassInfo> find_class(const TSNode& node,
                                  std::string_view source_code);
std::vector<FieldInfo> get_field(const TSNode& node,
                                 std::string_view source_code);

export namespace TS {
class Parser {
public:
    Parser();
    ~Parser();

    std::optional<SchemaInfo> parse_cpp(std::filesystem::path filename);

private:
    TSParser* parser;
    const TSLanguage* language;
};
}  // namespace TS
