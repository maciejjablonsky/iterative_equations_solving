cmake_minimum_required(VERSION 3.15)
project(iterative_equations_solving C)
set(C_FLAGS "-Wall -Werror --std=c99 -O")
set(CMAKE_C_FLAGS "${C_FLAGS}")
include_directories(include)
include_directories(internals)

set(SOURCE_FILES matrix.c main.c matrix_internals.c)
add_executable(isolve ${SOURCE_FILES})