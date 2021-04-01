cmake_minimum_required(VERSION 3.15)
project(lab3_car)

set(CMAKE_CXX_STANDARD 20)

# Main
add_executable(car main.cpp car/Car.cpp car/Car.h car/direction/Direction.h)

# Tests
add_executable(car_tests tests/car_tests.cpp car/Car.cpp car/Car.h car/direction/Direction.h)