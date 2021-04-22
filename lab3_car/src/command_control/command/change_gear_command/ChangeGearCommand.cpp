#include "ChangeGearCommand.h"

ChangeGearCommand::ChangeGearCommand(Car& car, int newGear)
	: car(car)
	, newGear(newGear)
{
}

bool ChangeGearCommand::Execute()
{
	return car.SetGear(newGear);
}
