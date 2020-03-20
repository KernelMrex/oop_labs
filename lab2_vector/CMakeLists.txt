cmake_minimum_required(VERSION 3.15)
project(lab2_vector)

set(CMAKE_CXX_STANDARD 20)

# Main
add_executable(vector main.cpp vector_functions.h vector_functions.cpp)

# Tests
add_executable(vector_tests tests/tests.cpp vector_functions.h vector_functions.cpp tests/catch.hpp)