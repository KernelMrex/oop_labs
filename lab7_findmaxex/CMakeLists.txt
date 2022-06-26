cmake_minimum_required(VERSION 3.14)
project(lab7_findmaxex)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        findmaxex
        src/main.cpp
        src/lib/find_max_ex.h
)

add_executable(
        findmaxex_unit_tests
        test/unit/catch_main.cpp
        src/lib/find_max_ex.h
        test/unit/lib/find_max_ex_test.cpp
)