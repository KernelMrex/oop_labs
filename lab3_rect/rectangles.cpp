#include "rectangles.h"
#include "string_utils.h"
#include <string>

/**
 * Command syntax: <command> <obj id> <arg1> <arg2> <arg3> <arg4>
 */
std::optional<std::vector<CRectangle>> ParseRectangles(std::istream& in)
{
	std::vector<CRectangle> rectangles;
	for (std::string line; std::getline(in, line);)
	{
		std::vector<std::string> commandParams;
		split(line, commandParams, ' ');

		CRectangleCommands commandType;

		// Parse command
		if (commandParams[0] == "new")
		{
			commandType = CRectangleCommands::NEW;
		}
		else if (commandParams[0] == "scale")
		{
			commandType = CRectangleCommands::SCALE;
		}
		else if (commandParams[0] == "move")
		{
			commandType = CRectangleCommands::MOVE;
		}
		else
		{
			return std::nullopt;
		}

		// Parse obj
		int objId = std::stoi(commandParams[1]);
		switch (commandType)
		{
		case CRectangleCommands::NEW:
			if (objId != rectangles.size())
			{
				return std::nullopt;
			}
			break;
		case CRectangleCommands::SCALE:
		case CRectangleCommands::MOVE:
			if (!(objId >= 0 && objId < rectangles.size()))
			{
				return std::nullopt;
			}
			break;
		}

		// Parse arguments
		// TODO: ...
	}
}
