if(NOT ANDROID)
    set(STD_MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mingw)
else()
    set(STD_MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)
endif()
add_library(std STATIC)
target_sources(std
    PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        ${STD_MODULE_DIR}/std.cppm ${STD_MODULE_DIR}/std.compat.cppm)

