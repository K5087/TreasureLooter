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

    std::filesystem::create_directories(output_dir / "lua");
    // generate lua
    for (auto& info : manager.infos) {
        std::string code = lua::generateSchemaCode(info);
        auto filename = info.filename.filename();
        filename.replace_extension(".lua");
        std::ofstream file(output_dir / "lua" / filename);
        file.write(code.c_str(), code.length());
    }

    std::filesystem::create_directories(output_dir / "cpp");
    // generate serialize
    for (auto& info : manager.infos) {
        std::string serialize_code = cpp::serialize::generate(info);
        auto filename = info.filename.filename();
        filename.replace_extension(".cppm");
        std::ofstream serialize_file(output_dir / "cpp/serialize" / filename);
        serialize_file.write(serialize_code.c_str(), serialize_code.length());

        // generate display
        std::string display_code = cpp::display::generate(info);
        std::ofstream display_file(output_dir / "cpp/display" / filename);
        display_file.write(display_code.c_str(), display_code.length());
    }

    return 0;
}
