cmake_minimum_required(VERSION 3.15)
project(lab2_simple)

set(CMAKE_CXX_STANDARD 20)

add_executable(simple main.cpp prime_numbers.cpp prime_numbers.h)

add_executable(simple_tests tests/tests.cpp prime_numbers.cpp prime_numbers.h)
