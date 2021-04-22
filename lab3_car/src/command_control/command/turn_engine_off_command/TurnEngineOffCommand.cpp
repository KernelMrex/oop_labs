#include "TurnEngineOffCommand.h"

TurnEngineOffCommand::TurnEngineOffCommand(Car& car)
	: car(car)
{
}

bool TurnEngineOffCommand::execute()
{
	return car.TurnEngineOff();
}
