cmake_minimum_required(VERSION 3.0.0)
project(megcc 
    VERSION 0.1.0
    DESCRIPTION "meg c compilerr"
    LANGUAGES C
)

include(CTest)
enable_testing()

add_executable(me9cc me9cc/main.c)

# Run Test for return integer functions
macro(execute_test test_name)
    file(GLOB INPUT_EQUAL_INTEGER me9cc/tests/asset/equal_integer/*)
    file(COPY ${INPUT_EQUAL_INTEGER} DESTINATION tests/equal_integer)
    add_custom_command(
        OUTPUT ${test_name}.s
        COMMAND $<TARGET_FILE:me9cc> tests/equal_integer/input/${test_name} ${test_name}.s ret_int
    )
    set_property(SOURCE ${test_name}.s PROPERTY LANGUAGE C)
    add_executable(test_${test_name} me9cc/tests/equal_integer.c ${test_name}.s)
    target_include_directories(test_${test_name} PRIVATE me9cc/tests/include)
    add_test(
        NAME test_${test_name}
        COMMAND $<TARGET_FILE:test_${test_name}> tests/equal_integer/output/${test_name}
        CONFIGURATIONS Debug
    )
endmacro()

execute_test(a_int)
execute_test(add_and_sub)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
