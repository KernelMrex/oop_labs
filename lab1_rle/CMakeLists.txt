cmake_minimum_required(VERSION 3.14)
project(lab1_rle)

set(CMAKE_CXX_STANDARD 20)

add_executable(rle src/main.cpp src/lib/Args.h src/lib/ActionEnum.h src/lib/RleCompressor.h)

add_executable(
        rle_unit_tests
        test/catch_main.cpp

        # Args unit tests
        src/lib/Args.h
        src/lib/ActionEnum.h
        test/lib/TestArgs.cpp

        # RleCompressor unit tests
        src/lib/RleCompressor.h
        test/lib/TestRleCompressor.cpp
)