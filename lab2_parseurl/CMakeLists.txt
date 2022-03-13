cmake_minimum_required(VERSION 3.14)
project(lab2_parseurl)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        parseurl
        src/main.cpp
)

add_executable(
        parseurl_unit_tests
        test/unit/catch_main.cpp
)