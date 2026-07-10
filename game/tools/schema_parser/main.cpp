#include "tool.hpp"

#include <argp/argp.h>
#include <tree_sitter/api.h>

#include <filesystem>
#include <fstream>
#include <iostream>

extern "C" const TSLanguage* tree_sitter_cpp(void);

void parse_cpp(const std::filesystem::path& filename) {
    std::cout << "parsing " << filename << std::endl;
    // tree-sitter init
    TSParser* parser = ts_parser_new();
    ts_parser_set_language(parser, tree_sitter_cpp());

    // read file
    std::ifstream file(filename);
    if (file.fail()) {
        std::cerr << "Failed to open fileu: " << filename << '\n';
        return;
    }
    std::string source_code(std::istreambuf_iterator<char>(file), {});

    // parse content
    TSTree* tree = ts_parser_parse_string(parser, nullptr, source_code.c_str(),
                                          source_code.size());
    if (!tree) {
        std::cerr << "Failed to parse cpp\n";
        return;
    }
    TSNode root_node = ts_tree_root_node(tree);

    std::string_view string = get_node_string(root_node, source_code);
    std::cout << string << std::endl;

    // destroy tree-sitter
    ts_tree_delete(tree);
    ts_parser_delete(parser);
}

int main(int argc, char** argv) {
    std::filesystem::path parse_dir;
    std::filesystem::path output_dir = "generate";
    std::filesystem::path src_prefix;

    os::argp::Parser parser;
    parser.add_pos("parse_dir", true, "parse directory",
                   os::argp::Boundary::one_arg);
    parser.add_option({"-o", "--output"}, "output directory",
                      os::argp::Boundary::one_arg);
    parser.add_option({"--src-prefix"}, "src prefix",
                      os::argp::Boundary::one_arg);
    try {
        parser.parse(argc, argv);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
        return 0;
    }

    auto parse_dirs = parser.get_pos(0);
    if (parse_dirs.empty()) {
        std::cout << "parse directory is empty" << std::endl;
        return 0;
    }

    parse_dir = parse_dirs[0];
    if (!std::filesystem::exists(parse_dir)) {
        std::cout << "parse directory is not exist" << std::endl;
        return 0;
    }

    std::vector<std::filesystem::path> cpp_files;
    for (const auto& entry : std::filesystem::directory_iterator(parse_dir)) {
        if (!entry.is_regular_file()) {
            continue;
        }
        if (entry.path().extension() == ".cppm") {
            cpp_files.push_back(entry.path());
        }
    }

    parse_cpp(cpp_files[0]);

    return 0;
}
