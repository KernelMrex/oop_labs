cmake_minimum_required(VERSION 3.15)
project(lab2_decode)

set(CMAKE_CXX_STANDARD 20)

add_executable(decode main.cpp decode.cpp)

add_executable(decode_tests tests/tests.cpp decode.cpp)