#ifndef INCLUDE_TURN_ENGINE_ON_COMMAND_H
#define INCLUDE_TURN_ENGINE_ON_COMMAND_H

#include "../Command.h"

class TurnEngineOnCommand : public Command
{
public:
	explicit TurnEngineOnCommand(Car& car);

	bool Execute() override;

private:
	Car& car;
};

#endif
