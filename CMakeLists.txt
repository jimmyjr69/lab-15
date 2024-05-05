cmake_minimum_required(VERSION 3.26)
project(untitled1 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled1 main.c
        libs/algorithms/algorithm.c
        libs/algorithms/algorithm.h
        libs/algorithms/array/array.c
        libs/algorithms/array/array.h
        libs/data_structures/bitset/bitset.c
        libs/data_structures/bitset/bitset.h
        libs/algorithms/for_dm/for_dm.h
        libs/string_/string_.c
        libs/string_/string_.h)
add_subdirectory(libs)
target_link_libraries(untitled1 algorithms)
target_link_libraries(untitled1 data_structures)