#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace os::argp {
enum class Boundary {
    get_self,
    one_arg,
    another_rule,
};

struct Rule {
    Boundary boundary;
};

class Option {
public:
    std::vector<std::string_view> keys;
    std::vector<std::string_view> args;
    std::string_view help;
    Rule rule;
};

class PosOption {
public:
    std::string name;
    std::vector<std::string_view> args;
    std::string_view help;
    Rule rule;
    bool required;

    void handle_rule(class Parser &parser, int &index, int argc, char **argv);
};

class Parser {
public:
    void parse(int argc, char **argv);

    void add_option(std::vector<std::string_view> keys, std::string_view help,
                    Boundary boundary);
    void add_pos(std::string_view name, bool required, std::string_view help,
                 Boundary boundary);

    std::vector<std::string_view> &get_args(std::string_view key);
    std::vector<std::string_view> &get_pos(size_t pos);

    void print_helper(std::string_view name);

    bool is_option(std::string_view arg);

private:
    std::vector<Option> options;
    std::vector<PosOption> posoptions;

    std::unordered_map<std::string_view, std::size_t> index;
};

}  // namespace os::argp
