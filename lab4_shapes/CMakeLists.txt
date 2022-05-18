cmake_minimum_required(VERSION 3.14)
project(lab4_shapes)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        shapes
        src/main.cpp
        src/lib/CPoint.cpp
        src/lib/CPoint.h
        src/lib/IShape.h
        src/lib/CLineSegment.cpp
        src/lib/CLineSegment.h
        src/lib/ISolidShape.h
        src/lib/CTriangle.cpp
        src/lib/CTriangle.h
        src/lib/CRectangle.cpp src/lib/CRectangle.h)

add_executable(
        shapes_unit_tests
        test/unit/catch_main.cpp
        src/lib/CPoint.cpp
        src/lib/CPoint.h
        test/unit/lib/CPointTest.cpp
        src/lib/CLineSegment.cpp
        src/lib/CLineSegment.h
        test/unit/lib/CLineSegmentTest.cpp
        src/lib/ISolidShape.h
        src/lib/CTriangle.cpp
        src/lib/CTriangle.h
        test/unit/lib/CTriangleTest.cpp
        src/lib/CRectangle.cpp src/lib/CRectangle.h test/unit/lib/CRectangleTest.cpp)