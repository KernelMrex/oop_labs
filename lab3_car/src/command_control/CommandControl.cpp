#include "CommandControl.h"

CommandControl::CommandControl(Car& car)
	: car(car)
{
}

void CommandControl::ListenAndServe(std::istream& in, std::ostream& out) const
{
	std::string instruction;
	while (std::getline(in, instruction))
	{
		std::unique_ptr<CommandInterface> command = std::move(CommandParser::parseString(instruction));
		Result result(command->execute(car));
		if (result.IsSuccessful())
		{
			out << result.GetMessage() << std::endl;
		}
		else
		{
			out << "Command execution failed" << std::endl;
		}
	}
}