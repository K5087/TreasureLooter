#pragma once

#include <string_view>
#include <tree_sitter/api.h>

inline std::string_view get_node_string(TSNode node,
                                        std::string_view source_code) {
    auto s = ts_node_start_byte(node);
    auto e = ts_node_end_byte(node);
    return source_code.substr(s, e - s);
}
