cmake_minimum_required(VERSION 3.15)
project(lab2_encode)

set(CMAKE_CXX_STANDARD 20)

add_executable(encode main.cpp encode.cpp)

add_executable(encode_tests tests/tests.cpp encode.cpp)