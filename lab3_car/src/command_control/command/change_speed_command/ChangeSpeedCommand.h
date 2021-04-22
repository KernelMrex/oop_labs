#ifndef INCLUDE_CHANGE_SPEED_COMMAND_H
#define INCLUDE_CHANGE_SPEED_COMMAND_H

#include "../Command.h"

class ChangeSpeedCommand : public Command
{
public:
	ChangeSpeedCommand(Car &car, int newSpeed);

	bool execute() override;

private:
	Car& car;
	int newSpeed;
};

#endif
