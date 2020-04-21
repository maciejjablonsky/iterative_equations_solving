cmake_minimum_required(VERSION 3.15)
project(iterative_equations_solving C)
set(C_FLAGS "-Wall -Werror --std=c99 -O")
set(CMAKE_C_FLAGS "${C_FLAGS}")
include_directories(include)
include_directories(internals)

set(SOURCE_FILES matrix.c vector.c helper.c linear_equations.c)
add_executable(time ${SOURCE_FILES} main.c)
target_link_libraries(time m)

add_executable(execution_measure execution_test.c ${SOURCE_FILES})
target_link_libraries(execution_measure m)