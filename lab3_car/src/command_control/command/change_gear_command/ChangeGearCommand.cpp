#include "ChangeGearCommand.h"

Result ChangeGearCommand::execute(Car& car)
{
	return Result(car.SetGear(newGear));
}
