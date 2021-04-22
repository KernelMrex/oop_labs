#include "../Command.h"

#ifndef INCLUDE_CHANGE_GEAR_COMMAND_H
#define INCLUDE_CHANGE_GEAR_COMMAND_H

class ChangeGearCommand : public Command
{
public:
	ChangeGearCommand(Car &car, int newGear);

	bool Execute() override;

private:
	Car& car;
	int newGear;
};

#endif
