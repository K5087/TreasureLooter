cmake_minimum_required(VERSION 4.0)

################# toolchain setting #####################
include(cmake/cpp.toolchain.cmake)

################# project setting #####################
project(TreasureLooter
    VERSION 0.0.1
    LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################# compile vendor #####################
include(cmake/add_vendor.cmake)
add_subdirectory(vendor)

########### generate project path file ###############
configure_file(project_generator.cpp ${CMAKE_CURRENT_SOURCE_DIR}/project.cpp)

################ compile tools ######################
if(NOT ANDROID)
    add_subdirectory(tools)
endif()

################ run schema_parser ######################
set(SCHEMA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/module/type)
file(GLOB_RECURSE TYPES ${SCHEMA_DIR}/*.cppm)
file(GLOB_RECURSE MUSTACHES ./tools/schema_parser/template/*.mustache)
set(SCHEMA_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/schema/")
set(SCHEMA_OUTPUT_FILES)
set(SCHEMA_OUTPUT_MODULE_FILES)
set(schema_lua_path "${SCHEMA_OUTPUT_PATH}/lua")
set(schema_cpp_path "${SCHEMA_OUTPUT_PATH}/cpp")
foreach(schema ${TYPES})
    cmake_path(GET schema FILENAME schema_filename)
    cmake_path(REPLACE_EXTENSION schema_filename ".lua" OUTPUT_VARIABLE schema_generate_lua)
    cmake_path(REPLACE_EXTENSION schema_filename ".cppm" OUTPUT_VARIABLE schema_generate_cppm)
    list(APPEND SCHEMA_OUTPUT_FILES
        ${schema_lua_path}/${schema_generate_lua}
        ${schema_cpp_path}/serialize/${schema_generate_cppm}
        ${schema_cpp_path}/display/${schema_generate_cppm}
    )
    list(APPEND SCHEMA_OUTPUT_MODULE_FILES
        ${schema_cpp_path}/serialize/${schema_generate_cppm}
        ${schema_cpp_path}/display/${schema_generate_cppm}
    )
endforeach()

if(NOT ANDROID)
    add_custom_command(OUTPUT ${SCHEMA_OUTPUT_FILES}
    COMMAND $<TARGET_FILE:schema_parser> ${SCHEMA_DIR} --output=${SCHEMA_OUTPUT_PATH} --src-prefix = "./"
    DEPENDS $<TARGET_FILE:schema_parser> ${TYPES} ${MUSTACHES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "parsing schemas..."
)
endif()

################ compile game ######################

file(GLOB_RECURSE HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/header/*.hpp)
file(GLOB_RECURSE MODULE ${CMAKE_CURRENT_SOURCE_DIR}/src/module/*.cppm)
file(GLOB_RECURSE IMPL ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/project.cpp )
file(GLOB_RECURSE ASSETS ./assets/*)

set(TL_ENABLE_EDITOR_MODE ON)

set(GAME_NAME ${PROJECT_NAME})
if (ANDROID)
    set(GAME_NAME main)
    set(TL_ENABLE_EDITOR_MODE OFF)
    add_library(${GAME_NAME} SHARED)
else()
    add_executable(${GAME_NAME})
endif()

target_sources(${GAME_NAME}
    PRIVATE
    ${HEADER} ${ASSETS} ${IMPL}
    PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        ${MODULE} ${SCHEMA_OUTPUT_MODULE_FILES}
)
target_include_directories(${GAME_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/header)
target_link_libraries(${GAME_NAME} PRIVATE SDL3::SDL3 spdlog::spdlog stb_image imgui simdjson std stduuid)
target_compile_definitions(${GAME_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
target_compile_definitions(${GAME_NAME} PUBLIC $<$<AND:$<CONFIG:Debug>,$<BOOL:${TL_ENABLE_EDITOR_MODE}>>:TL_ENABLE_EDITOR>)
# set_property(TARGET ${GAME_NAME} PROPERTY CXX_MODULE_STD ON)

################ install #######################
install(TARGETS ${GAME_NAME} DESTINATION .)
install(DIRECTORY assets DESTINATION .)

################ package ##################
# include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_GENERATOR "ZIP")
set(CPACK_SOURCE_GENERATOR "ZIP")
include(CPack)
