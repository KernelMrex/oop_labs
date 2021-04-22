#ifndef INCLUDE_COMMAND_H
#define INCLUDE_COMMAND_H

#include "../../car/Car.h"

class Command
{
public:
	virtual bool Execute() = 0;

	virtual ~Command() = default;
};

#endif
