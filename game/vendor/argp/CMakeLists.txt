set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(argp STATIC src/argp.cpp)

target_sources(argp
    PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        ${INCLUDE_DIR}/argp/argp.cppm)
target_link_libraries(argp PRIVATE std)
