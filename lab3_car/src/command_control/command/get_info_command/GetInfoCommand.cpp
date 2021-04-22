#include "GetInfoCommand.h"
#include <sstream>

GetInfoCommand::GetInfoCommand(const Car& car, std::ostream& ostream)
	: car(car)
	, output(ostream)
{
}

bool GetInfoCommand::execute()
{
	std::string direction;
	switch (car.GetDirection())
	{
	case Direction::FORWARD:
		direction = "forward";
		break;
	case Direction::BACKWARD:
        direction = "backward";
		break;
	case Direction::STILL:
        direction = "still";
		break;
	}

	output
		<< "Direction: " << direction << std::endl
	    << "Speed:     " << car.GetSpeed() << std::endl
	    << "Gear:      " << car.GetGear() << std::endl
		<< "Engine:    " << (car.IsEngineTurnOn() ? "on" : "off") << std::endl;

	return true;
}
