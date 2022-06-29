cmake_minimum_required(VERSION 3.14)
project(lab7_cmylist)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        cmylist
        src/main.cpp
        src/lib/CMyList.h
        src/lib/CMyListException.cpp
        src/lib/CMyListException.h
)

add_executable(
        cmylist_unit_tests
        test/unit/catch_main.cpp
        src/lib/CMyList.h
        test/unit/lib/CMyListTest.cpp
        src/lib/CMyListException.cpp
        src/lib/CMyListException.h
)