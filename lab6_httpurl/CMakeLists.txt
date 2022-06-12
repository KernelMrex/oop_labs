cmake_minimum_required(VERSION 3.14)
project(lab6_httpurl)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        httpurl
        src/main.cpp
        src/lib/CHttpUrl/Protocol.h
        src/lib/CHttpUrl/CHttpUrl.cpp
        src/lib/CHttpUrl/CHttpUrl.h
        src/lib/CHttpUrl/Exception/CUrlParsingError.cpp
        src/lib/CHttpUrl/Exception/CUrlParsingError.h
)

add_executable(
        httpurl_unit_tests
        test/unit/catch_main.cpp
        src/lib/CHttpUrl/CHttpUrl.cpp
        src/lib/CHttpUrl/CHttpUrl.h
        src/lib/CHttpUrl/Exception/CUrlParsingError.cpp
        src/lib/CHttpUrl/Exception/CUrlParsingError.h
        test/unit/lib/CHttpUrlTest.cpp
)