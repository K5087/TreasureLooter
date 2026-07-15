cmake_minimum_required(VERSION 4.0)

################# toolchain setting #####################
include(cmake/llvm.toolchain.cmake)

################# project setting #####################
project(TreasureLooter
    VERSION 0.0.1
    LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################# compile vendor #####################
include(cmake/add_vendor.cmake)
add_subdirectory(vendor)

################ compile tools ######################
if(NOT ANDROID)
    add_subdirectory(tools)
endif()



################ compile game ######################

file(GLOB_RECURSE HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/header/*.hpp)
file(GLOB_RECURSE MODULE ${CMAKE_CURRENT_SOURCE_DIR}/src/module/*.cppm ${CMAKE_CURRENT_SOURCE_DIR}/schema/cpp/*.cppm)
file(GLOB_RECURSE IMPL ${CMAKE_CURRENT_SOURCE_DIR}/src/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )
file(GLOB_RECURSE ASSETS ./assets/*)

set(GAME_NAME ${PROJECT_NAME})
if (ANDROID)
    set(GAME_NAME main)
    add_library(${GAME_NAME} SHARED)
else()
    add_executable(${GAME_NAME})
endif()

target_sources(${GAME_NAME}
    PRIVATE
    ${HEADER} ${ASSETS} ${IMPL}
    PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
            ${MODULE}
)
target_include_directories(${GAME_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/header)
target_link_libraries(${GAME_NAME} PRIVATE SDL3::SDL3 spdlog::spdlog stb_image imgui simdjson)
target_compile_definitions(${GAME_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
set_property(TARGET ${GAME_NAME} PROPERTY CXX_MODULE_STD ON)

################ run schema_parser ######################
file(GLOB_RECURSE MUSTACHES ./tools/schema_parser/templet/*.mustache)
set(SCHEMA_OUTPUT_PATH "schema/")
set(SCHEMA_OUTPUT_FILES)
foreach(schema ${MODULE})
    cmake_path(GET schema FILENAME schema_filename)
    cmake_path(REPLACE_EXTENSION schema_filename ".lua" OUTPUT_VARIABLE schema_generate_lua)
    set(schema_final_path "${CMAKE_CURRENT_SOURCE_DIR}/${SCHEMA_OUTPUT_PATH}/${schema_generate_lua}")
    list(APPEND SCHEMA_OUTPUT_FILES ${schema_final_path})
endforeach()

add_custom_command(OUTPUT ${SCHEMA_OUTPUT_FILES}
    COMMAND $<TARGET_FILE:schema_parser> ./schema --output=${SCHEMA_OUTPUT_PATH} --src-prefix = "./"
    DEPENDS $<TARGET_FILE:schema_parser> ${MODULE} ${MUSTACHES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "parsing schemas..."
)

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
