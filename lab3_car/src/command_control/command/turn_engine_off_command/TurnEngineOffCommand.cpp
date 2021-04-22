#include "TurnEngineOffCommand.h"

TurnEngineOffCommand::TurnEngineOffCommand(Car& car)
	: car(car)
{
}

bool TurnEngineOffCommand::Execute()
{
	return car.TurnEngineOff();
}
