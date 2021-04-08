cmake_minimum_required(VERSION 3.15)
project(lab3_car)

set(CMAKE_CXX_STANDARD 20)

# Main
add_executable(
        car
        src/main.cpp
        src/car/Car.cpp
        src/car/Car.h
        src/car/direction/Direction.h
        src/command_control/CommandControl.cpp
        src/command_control/CommandControl.h
        src/command_control/command_parser/CommandParser.cpp
        src/command_control/command_parser/CommandParser.h
        src/command_control/command/CommandInterface.h
        src/command_control/result/Result.cpp
        src/command_control/result/Result.h
        src/command_control/command/get_info_command/GetInfoCommand.cpp
        src/command_control/command/get_info_command/GetInfoCommand.h
        src/command_control/command/change_gear_command/ChangeGearCommand.cpp src/command_control/command/change_gear_command/ChangeGearCommand.h)

# Tests
add_executable(
        car_tests
        tests/car_tests.cpp
        src/car/Car.cpp
        src/car/Car.h
        src/car/direction/Direction.h
)