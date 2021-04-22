#ifndef INCLUDE_TURN_ENGINE_OFF_COMMAND_H
#define INCLUDE_TURN_ENGINE_OFF_COMMAND_H

#include "../Command.h"

class TurnEngineOffCommand : public Command
{
public:
	explicit TurnEngineOffCommand(Car& car);

	bool execute() override;

private:
	Car& car;
};

#endif
