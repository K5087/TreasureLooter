import parser;
import common;
import os.argp;
import generate;
import std;

int main(int argc, char** argv) {
    std::cout << std::filesystem::current_path() << std::endl;
    // arg parse
    os::argp::Parser parser;
    std::filesystem::path parse_dir;
    std::filesystem::path output_dir = "schema";
    std::filesystem::path src_prefix;
    parser.add_pos("parse_dir", true, "parse directory",
                   os::argp::Boundary::one_arg);
    parser.add_opt({"-o", "--output"}, "output directory",
                   os::argp::Boundary::one_arg);
    parser.add_opt({"--src-prefix"}, "src prefix", os::argp::Boundary::one_arg);
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

    // cpp file parse
    TS::Parser cpp_parser;
    std::vector<std::filesystem::path> cpp_files;
    for (const auto& entry : std::filesystem::directory_iterator(parse_dir)) {
        if (!entry.is_regular_file()) {
            continue;
        }
        if (entry.path().extension() == ".cppm") {
            cpp_files.push_back(entry.path().lexically_normal());
        }
    }

    SchemaManager manager;
    for (auto& filename : cpp_files) {
        auto schema_info = cpp_parser.parse_cpp(filename);
        if (schema_info) {
            manager.infos.push_back(schema_info.value());
        }
    }
    std::filesystem::path lua_path = output_dir / "lua";
    std::filesystem::path cpp_serialize_path = output_dir / "cpp/serialize";
    std::filesystem::path cpp_display_path = output_dir / "cpp/display";

    std::filesystem::create_directories(lua_path);
    std::filesystem::create_directories(cpp_serialize_path);
    std::filesystem::create_directories(cpp_display_path);

    for (auto& info : manager.infos) {
        // generate lua
        std::string code = lua::generateSchemaCode(info);
        auto lua_filename = info.filename.filename();
        lua_filename.replace_extension(".lua");
        std::ofstream file(lua_path / lua_filename);
        file.write(code.c_str(), code.length());

        // generate serialize
        std::string serialize_code = cpp::serialize::generate(info);
        auto cpp_filename = info.filename.filename();
        cpp_filename.replace_extension(".cppm");
        std::ofstream serialize_file(cpp_serialize_path / cpp_filename);
        serialize_file.write(serialize_code.c_str(), serialize_code.length());

        // generate display
        std::string display_code = cpp::display::generate(info);
        std::ofstream display_file(cpp_display_path / cpp_filename);
        display_file.write(display_code.c_str(), display_code.length());
    }

    for (auto& info : manager.infos) {
    }

    return 0;
}
