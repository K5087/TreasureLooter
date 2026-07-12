function(
    add_module_library
    target_name
    lib_type
    include_dir_var
    source_var
    module_var
)
    add_library(${target_name} ${lib_type})

    set_target_properties(${target_name} PROPERTIES CXX_MODULE_STD ON)

    target_include_directories(${target_name} PUBLIC ${${include_dir_var}})

    target_sources(
        ${target_name}
        PRIVATE ${${source_var}}
        PUBLIC
            FILE_SET CXX_MODULES
                BASE_DIRS ${${include_dir_var}}
                FILES ${${module_var}}
    )
endfunction()

function(add_module_test target_name)
    add_executable(${target_name}_test ${target_name}/main.cpp)
    target_link_libraries(${target_name}_test PRIVATE ${target_name}_static)

    set_target_properties(${target_name}_test PROPERTIES CXX_MODULE_STD ON)
    add_test(NAME ${target_name}_test COMMAND ${target_name}_test)
endfunction()
