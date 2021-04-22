#include "../Command.h"
#include <ostream>

#ifndef INCLUDE_GET_INFO_COMMAND_H
#define INCLUDE_GET_INFO_COMMAND_H

class GetInfoCommand : public Command
{
public:
	GetInfoCommand(const Car&, std::ostream&);

	bool Execute() override;

private:
	const Car& car;
	std::ostream& output;
};

#endif
