cmake_minimum_required(VERSION 3.14)
project(lab7_cmylist)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        cmylist
        src/main.cpp
)

add_executable(
        cmylist_unit_tests
        test/unit/catch_main.cpp
)