#include "ChangeSpeedCommand.h"

ChangeSpeedCommand::ChangeSpeedCommand(Car& car, int newSpeed)
	: car(car)
	, newSpeed(newSpeed)
{
}

bool ChangeSpeedCommand::execute()
{
	return car.SetSpeed(newSpeed);
}