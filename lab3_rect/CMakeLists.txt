cmake_minimum_required(VERSION 3.15)
project(lab3_rect)

set(CMAKE_CXX_STANDARD 20)

add_executable(rect main.cpp CRectangle.cpp CRectangle.h Point2D.cpp Point2D.h)

add_executable(rect_tests ../../catch.hpp tests/tests.cpp CRectangle.cpp CRectangle.h Point2D.cpp Point2D.h)