cmake_minimum_required(VERSION 3.15)
project(iterative_solving_equations C)
include_directories(../vendor/ceedling/vendor/unity/src)
include_directories(../vendor/ceedling/vendor/cmock/src)
include_directories(../vendor/ceedling/vendor/c_exception/lib)
include_directories(../src/include)
include_directories(../vendor/plugins)
include_directories(../build/test/mocks)
include_directories(../vendor/ceedling/plugins/fake_function_framework/src)
include_directories(support)
set(TESTS_SOURCE test_matrix.c
        test_vector.c
        test_linear_equations.c
        support/unity_config.h
        support/matrix_test_helper.h support/matrix_test_helper.c)

add_executable(dummy_test ${TESTS_SOURCE})
