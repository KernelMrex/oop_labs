#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../src/car/Car.h"
#include "../src/command_control/CommandControl.h"

TEST_CASE("Get Info", "[get_info]")
{
	Car car;
	std::stringstream in;
	in << "Info\n";
	std::stringstream out;
	auto commandControl = CommandControl(car, in, out);
	commandControl.ListenAndServe();
	REQUIRE(in.eof());
	REQUIRE(out.str() == "Direction: still\n"
						 "Speed:     0\n"
						 "Gear:      0\n"
						 "Engine:    off\n"
						 "Command Execute success\n");
}

TEST_CASE("Get info after gear change and speed up", "[get_info_after_gear_change_and_speed_up]")
{
	Car car;
	std::stringstream in;
	in << "EngineOn\n" << "SetGear 1\n" << "SetSpeed 20\n" << "Info\n";
	std::stringstream out;
	auto commandControl = CommandControl(car, in, out);
	commandControl.ListenAndServe();
	REQUIRE(in.eof());
	REQUIRE(out.str() == "Command Execute success\n"
						 "Command Execute success\n"
						 "Command Execute success\n"
						 "Direction: forward\n"
						 "Speed:     20\n"
						 "Gear:      1\n"
						 "Engine:    on\n"
						 "Command Execute success\n");
}

TEST_CASE("Execute wrong command", "[execute_wrong_command]")
{
	Car car;
	std::stringstream in;
	in << "WrongCommand\n";
	std::stringstream out;
	auto commandControl = CommandControl(car, in, out);
	commandControl.ListenAndServe();
	REQUIRE(in.eof());
	REQUIRE(out.str() == "Unknown command\n");
}

TEST_CASE("Execute command with invalid arguments", "[execute_wrong_command]")
{
	Car car;
	std::stringstream in;
	in << "SetSpeed a\n";
	std::stringstream out;
	auto commandControl = CommandControl(car, in, out);
	commandControl.ListenAndServe();
	REQUIRE(in.eof());
	REQUIRE(out.str() == "Unknown command\n");
}
