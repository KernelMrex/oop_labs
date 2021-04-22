#include "TurnEngineOnCommand.h"

TurnEngineOnCommand::TurnEngineOnCommand(Car& car)
	: car(car)
{
}

bool TurnEngineOnCommand::Execute()
{
	return car.TurnEngineOn();
}
