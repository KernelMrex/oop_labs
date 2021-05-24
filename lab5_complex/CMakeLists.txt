cmake_minimum_required(VERSION 3.15)
project(lab3_car)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        complex
        src/main.cpp
        src/Complex/Complex.cpp
        src/Complex/Complex.h
)

add_executable(
        complex_tests
        test/test.cpp
        src/Complex/Complex.cpp
        src/Complex/Complex.h
)