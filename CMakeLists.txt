cmake_minimum_required(VERSION 3.0.0)
project(megcc 
    VERSION 0.1.0
    DESCRIPTION "meg c compilerr"
    LANGUAGES C
)

include(CTest)
enable_testing()

add_executable(me9cc ./me9cc/main.c)

# Run Test
file(GLOB test_inputs ./me9cc/tests/asset/input/a_int.me9c)
foreach(test_input ${test_inputs})
    get_filename_component(test_output_name ${test_input} NAME)
    add_custom_command(
        OUTPUT out.s
        COMMAND $<TARGET_FILE:me9cc> ${test_input} out.s
    )
    set_property(SOURCE out.s PROPERTY LANGUAGE C)
    add_executable(equal_integer ./me9cc/tests/equal_integer.c out.s)
    target_include_directories(equal_integer PRIVATE ./me9cc/tests/asset/include)
    add_test(
        NAME test_a_int
        COMMAND $<TARGET_FILE:equal_integer> ./me9cc/tests/asset/output/${test_output_name}.out
        CONFIGURATIONS Debug
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )
endforeach()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
