#include "CommandParser.h"
#include "../command/get_info_command/GetInfoCommand.h"
#include <memory>

std::unique_ptr<CommandInterface> CommandParser::parseString(const std::string& instruction)
{
	std::unique_ptr<CommandInterface> command;

	command = std::make_unique<GetInfoCommand>();

	return command;
}
