cmake_minimum_required(VERSION 3.14)
project(lab1_crypt)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        crypt
        src/main.cpp

        src/lib/Args.h
        src/lib/Action.h
        src/lib/CryptService.h
)

add_executable(
        crypt_unit_tests
        test/unit/catch_main.cpp

        src/lib/CryptService.h
        test/unit/lib/CryptServiceTest.cpp
        ../lab2_expand_template/test/unit/catch_main.cpp)