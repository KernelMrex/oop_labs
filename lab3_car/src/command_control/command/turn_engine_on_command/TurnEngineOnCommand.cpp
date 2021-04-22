#include "TurnEngineOnCommand.h"

TurnEngineOnCommand::TurnEngineOnCommand(Car& car)
	: car(car)
{
}

bool TurnEngineOnCommand::execute()
{
	return car.TurnEngineOn();
}
