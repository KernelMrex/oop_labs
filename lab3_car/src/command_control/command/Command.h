#include "../../car/Car.h"


#ifndef INCLUDE_COMMAND_H
#define INCLUDE_COMMAND_H

class Command
{
public:
	virtual bool Execute() = 0;

	virtual ~Command() = default;
};

#endif
