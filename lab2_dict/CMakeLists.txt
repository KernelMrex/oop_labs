cmake_minimum_required(VERSION 3.15)
project(lab2_dict)

set(CMAKE_CXX_STANDARD 20)

add_executable(dict main.cpp Dictionary.cpp Dictionary.h FileDictionary.cpp FileDictionary.h string_utils.cpp string_utils.h)

add_executable(dict_tests tests/tests.cpp Dictionary.cpp Dictionary.h string_utils.cpp string_utils.h)