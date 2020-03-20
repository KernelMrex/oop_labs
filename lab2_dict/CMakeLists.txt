cmake_minimum_required(VERSION 3.15)
project(lab2_dict)

set(CMAKE_CXX_STANDARD 20)

add_executable(dict main.cpp dictionary.cpp dictionary.h)

add_executable(dict_tests tests/tests.cpp dictionary.cpp dictionary.h)