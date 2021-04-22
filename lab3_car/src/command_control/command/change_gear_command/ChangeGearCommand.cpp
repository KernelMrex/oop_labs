#include "ChangeGearCommand.h"

ChangeGearCommand::ChangeGearCommand(Car& car, int newGear)
	: car(car)
	, newGear(newGear)
{
}

bool ChangeGearCommand::execute()
{
	return car.SetGear(newGear);
}
