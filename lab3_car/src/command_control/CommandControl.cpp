#include "CommandControl.h"
#include "command/change_gear_command/ChangeGearCommand.h"
#include "command/change_speed_command/ChangeSpeedCommand.h"
#include "command/get_info_command/GetInfoCommand.h"
#include "command/turn_engine_off_command/TurnEngineOffCommand.h"
#include "command/turn_engine_on_command/TurnEngineOnCommand.h"

CommandControl::CommandControl(Car& car, std::istream& in, std::ostream& out)
	: car(car)
	, in(in)
	, out(out)
{
}

void CommandControl::ListenAndServe() const
{
	while (!in.eof())
	{
		auto command = readCommand();
		if (command.has_value())
		{
			if (command.value()->execute())
			{
				out << "Command execute success" << std::endl;
			}
			else
			{
				out << "Command execute failed" << std::endl;
			}
		}
	}
}

std::optional<std::unique_ptr<Command>> CommandControl::readCommand() const
{
	std::string instruction;
	std::getline(in, instruction);

	auto commandType = getNextArgument(instruction);

	if (commandType == "Info")
	{
		return { std::make_unique<GetInfoCommand>(car, out) };
	}
	else if (commandType == "EngineOn")
	{
		return { std::make_unique<TurnEngineOnCommand>(car) };
	}
	else if (commandType == "EngineOff")
	{
		return { std::make_unique<TurnEngineOffCommand>(car) };
	}
	else if (commandType == "SetGear")
	{
		auto newGear = std::stoi(getNextArgument(instruction, commandType.length()));
		return { std::make_unique<ChangeGearCommand>(car, newGear) };
	}
	else if (commandType == "SetSpeed")
	{
		auto newSpeed = std::stoi(getNextArgument(instruction, commandType.length()));
		return { std::make_unique<ChangeSpeedCommand>(car, newSpeed) };
	}

	return std::nullopt;
}

std::string CommandControl::getNextArgument(const std::string& instruction, size_t prevDelimiterPos)
{
	auto lastDelimiterPos = instruction.find(' ', prevDelimiterPos);
	return instruction.substr(prevDelimiterPos, lastDelimiterPos);
}
