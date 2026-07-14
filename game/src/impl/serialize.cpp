module;
#include <simdjson.h>
module serialize;

import std;

template <typename T>
void serialize(std::string_view name, T& t) {
    std::cout << name << " " << t << std::endl;
}

template <typename T>
void deserialize(T& t, std::string_view name) {
    std::cout << name << " " << t << std::endl;
}
