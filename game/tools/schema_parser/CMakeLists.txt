file(GLOB_RECURSE SRC ./*.cpp ./*.hpp)

add_executable(schema_parser)
target_sources(schema_parser PRIVATE ${SRC})
target_link_libraries(schema_parser PRIVATE RapidXML argp tree-sitter tree-sitter-cpp)
