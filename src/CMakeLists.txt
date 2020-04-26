cmake_minimum_required(VERSION 3.15)
project(iterative_equations_solving C)
set(C_FLAGS "-Wall -Werror --std=c99 -O")
set(CMAKE_C_FLAGS "${C_FLAGS}")
include_directories(include)

set(SOURCE_FILES matrix.c vector.c linear_equations.c performance_test.c include/performance_test.h)
add_executable(exercise_report ${SOURCE_FILES} main.c)
target_link_libraries(exercise_report m)