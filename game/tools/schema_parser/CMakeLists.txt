add_subdirectory(mustache)
file(GLOB_RECURSE SOURCE ./*.cpp)
file(GLOB_RECURSE MODULE_SOURCE ./*.cppm)

add_executable(schema_parser)
target_link_libraries(schema_parser PRIVATE  argp tree-sitter tree-sitter-cpp mustache std)
target_sources(
    schema_parser
    PRIVATE ${SOURCE}
    PUBLIC
        FILE_SET CXX_MODULES
            FILES ${MODULE_SOURCE})
