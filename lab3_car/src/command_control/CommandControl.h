#include "../car/Car.h"
#include "command/Command.h"
#include <istream>
#include <memory>
#include <optional>

#ifndef INCLUDE_COMMAND_CONTROL_H
#define INCLUDE_COMMAND_CONTROL_H

class CommandControl
{
public:
	explicit CommandControl(Car& car, std::istream& in, std::ostream& out);

	void ListenAndServe() const;

private:
	[[nodiscard]] std::optional<std::unique_ptr<Command>> ReadCommand() const;
	[[nodiscard]] static std::string GetNextArgument(const std::string& instruction, size_t prevDelimiterPos = 0);

	Car& car;
	std::istream& in;
	std::ostream& out;
};

#endif