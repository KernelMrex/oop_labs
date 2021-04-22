#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../src/car/Car.h"
#include "../src/command_control/CommandControl.h"

TEST_CASE("Constructing car", "[construction]")
{
	Car car;

	REQUIRE(car.IsEngineTurnOn() == false);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetDirection() == Direction::STILL);
}

TEST_CASE("Turn on engine", "[turn_on]")
{
	Car car;
	REQUIRE(car.TurnEngineOn());

	REQUIRE(car.IsEngineTurnOn() == true);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetDirection() == Direction::STILL);
}

TEST_CASE("Turn on and off engine", "[turn_on_and_off]")
{
	Car car;
	REQUIRE(car.TurnEngineOn());

	REQUIRE(car.IsEngineTurnOn() == true);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetDirection() == Direction::STILL);

	REQUIRE(car.TurnEngineOff());
	REQUIRE(car.IsEngineTurnOn() == false);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetDirection() == Direction::STILL);
}

TEST_CASE("Speed up to 150 by lower border and turn off engine before and after each gear", "[speed_up_to_150__lower_border]")
{
	Car car;

	REQUIRE(car.TurnEngineOff());
	REQUIRE(car.TurnEngineOn());
	REQUIRE(car.SetGear(1));
	REQUIRE(!car.TurnEngineOff());

	REQUIRE(!car.TurnEngineOff());
	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.SetGear(2));
	REQUIRE(!car.TurnEngineOff());

	REQUIRE(!car.TurnEngineOff());
	REQUIRE(car.SetSpeed(30));
	REQUIRE(car.SetGear(3));
	REQUIRE(!car.TurnEngineOff());

	REQUIRE(!car.TurnEngineOff());
	REQUIRE(car.SetSpeed(40));
	REQUIRE(car.SetGear(4));
	REQUIRE(!car.TurnEngineOff());

	REQUIRE(!car.TurnEngineOff());
	REQUIRE(car.SetSpeed(50));
	REQUIRE(car.SetGear(5));
	REQUIRE(!car.TurnEngineOff());
}

TEST_CASE("Speed up to 150 by upper border and turn off engine before and after each gear", "[speed_up_to_150__upper_border]")
{
	Car car;
	REQUIRE(car.TurnEngineOn());
	REQUIRE(car.SetGear(1));
	REQUIRE(!car.SetSpeed(31));
	REQUIRE(car.SetSpeed(30));
	REQUIRE(!car.TurnEngineOff());

	REQUIRE(!car.TurnEngineOff());
	REQUIRE(car.SetGear(2));
	REQUIRE(!car.SetSpeed(51));
	REQUIRE(car.SetSpeed(50));
	REQUIRE(!car.TurnEngineOff());

	REQUIRE(!car.TurnEngineOff());
	REQUIRE(car.SetGear(3));
	REQUIRE(!car.SetSpeed(61));
	REQUIRE(car.SetSpeed(60));
	REQUIRE(!car.TurnEngineOff());

	REQUIRE(!car.TurnEngineOff());
	REQUIRE(car.SetGear(4));
	REQUIRE(!car.SetSpeed(91));
	REQUIRE(car.SetSpeed(90));
	REQUIRE(!car.TurnEngineOff());

	REQUIRE(!car.TurnEngineOff());
	REQUIRE(car.SetGear(5));
	REQUIRE(!car.SetSpeed(151));
	REQUIRE(car.SetSpeed(150));
	REQUIRE(!car.TurnEngineOff());
}

TEST_CASE("Slow down car from 150 to 0", "[slow_down_from_0_to_150__upper_border]")
{
	Car car;
	car.TurnEngineOn();
	REQUIRE(car.SetGear(1));
	REQUIRE(car.SetSpeed(30));
	REQUIRE(car.SetGear(2));
	REQUIRE(car.SetSpeed(50));
	REQUIRE(car.SetGear(3));
	REQUIRE(car.SetSpeed(60));
	REQUIRE(car.SetGear(4));
	REQUIRE(car.SetSpeed(90));
	REQUIRE(car.SetGear(5));
	REQUIRE(car.SetSpeed(150));

	REQUIRE(!car.TurnEngineOff());
	REQUIRE(!car.SetSpeed(49));
	REQUIRE(car.SetSpeed(50));
	REQUIRE(car.SetGear(4));
	REQUIRE(!car.TurnEngineOff());

	REQUIRE(!car.TurnEngineOff());
	REQUIRE(!car.SetSpeed(39));
	REQUIRE(car.SetSpeed(40));
	REQUIRE(car.SetGear(3));
	REQUIRE(!car.TurnEngineOff());

	REQUIRE(!car.TurnEngineOff());
	REQUIRE(!car.SetSpeed(29));
	REQUIRE(car.SetSpeed(30));
	REQUIRE(car.SetGear(2));
	REQUIRE(!car.TurnEngineOff());

	REQUIRE(!car.TurnEngineOff());
	REQUIRE(!car.SetSpeed(19));
	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.SetGear(1));
	REQUIRE(!car.TurnEngineOff());

	REQUIRE(!car.TurnEngineOff());
	REQUIRE(!car.SetSpeed(-1));
	REQUIRE(car.SetSpeed(0));
	REQUIRE(car.SetGear(0));
	REQUIRE(car.TurnEngineOff());
}

TEST_CASE("Set speed without turning car on", "[speed_up_without_engine_on]")
{
	Car car;
	REQUIRE(!car.IsEngineTurnOn());
	REQUIRE(!car.SetGear(1));
	REQUIRE(!car.SetSpeed(30));
	REQUIRE(!car.IsEngineTurnOn());
}

TEST_CASE("Moving backwards", "[moving_backwards]")
{
	Car car;
	REQUIRE(!car.IsEngineTurnOn());
	REQUIRE(car.GetDirection() == Direction::STILL);
	REQUIRE(!car.SetGear(-1));
	REQUIRE(!car.SetSpeed(20));
	REQUIRE(car.GetDirection() == Direction::STILL);

	REQUIRE(car.TurnEngineOn());
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.GetDirection() == Direction::BACKWARD);

	REQUIRE(car.SetGear(0));
	REQUIRE(car.SetSpeed(15));
	REQUIRE(!car.SetSpeed(20));
	REQUIRE(!car.SetGear(-1));
	REQUIRE(!car.SetGear(1));
	REQUIRE(car.GetSpeed() == 15);

	REQUIRE(car.SetSpeed(0));
}

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
