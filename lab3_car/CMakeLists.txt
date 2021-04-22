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
        src/command_control/command/Command.h
        src/command_control/command/get_info_command/GetInfoCommand.cpp
        src/command_control/command/get_info_command/GetInfoCommand.h
        src/command_control/command/change_gear_command/ChangeGearCommand.cpp
        src/command_control/command/change_gear_command/ChangeGearCommand.h
        src/command_control/command/turn_engine_on_command/TurnEngineOnCommand.cpp
        src/command_control/command/turn_engine_on_command/TurnEngineOnCommand.h
        src/command_control/command/turn_engine_off_command/TurnEngineOffCommand.cpp
        src/command_control/command/turn_engine_off_command/TurnEngineOffCommand.h
        src/command_control/command/change_speed_command/ChangeSpeedCommand.cpp
        src/command_control/command/change_speed_command/ChangeSpeedCommand.h
)

add_executable(
        command_control_tests
        tests/car_tests.cpp
        src/car/Car.cpp
        src/car/Car.h
        src/car/direction/Direction.h
        src/command_control/CommandControl.cpp
        src/command_control/CommandControl.h
        src/command_control/command/Command.h
        src/command_control/command/get_info_command/GetInfoCommand.cpp
        src/command_control/command/get_info_command/GetInfoCommand.h
        src/command_control/command/change_gear_command/ChangeGearCommand.cpp
        src/command_control/command/change_gear_command/ChangeGearCommand.h
        src/command_control/command/turn_engine_on_command/TurnEngineOnCommand.cpp
        src/command_control/command/turn_engine_on_command/TurnEngineOnCommand.h
        src/command_control/command/turn_engine_off_command/TurnEngineOffCommand.cpp
        src/command_control/command/turn_engine_off_command/TurnEngineOffCommand.h
        src/command_control/command/change_speed_command/ChangeSpeedCommand.cpp
        src/command_control/command/change_speed_command/ChangeSpeedCommand.h
)