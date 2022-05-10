cmake_minimum_required(VERSION 3.14)
project(lab2_expand_template)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        expand_template
        src/main.cpp
        src/lib/template_utils.h
        src/lib/template_utils.cpp
        src/lib/Graph.h
)

add_executable(
        expand_template_unit_tests
        test/unit/catch_main.cpp
        src/lib/template_utils.h
        src/lib/template_utils.cpp
        test/unit/lib/template_utils_test.cpp
        src/lib/Graph.h
        test/unit/lib/GraphTest.cpp
)