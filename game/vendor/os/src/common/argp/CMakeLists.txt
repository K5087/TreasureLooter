set(ARGP_DIR ${SOURCE_DIR}/argp)

set(ARGP_SOURCES argp.cpp)

add_library(argp INTERFACE ${ARGP_SOURCES})
target_include_directories(argp INTERFACE ${INCLUDE_DIR})
