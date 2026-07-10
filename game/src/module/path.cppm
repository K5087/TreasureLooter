module;
#include <spdlog/fmt/ostr.h>
export module path;

import std;

export using Path = std::filesystem::path;

// for spdlog output
export template <>
struct fmt::formatter<Path> : fmt::ostream_formatter {};
