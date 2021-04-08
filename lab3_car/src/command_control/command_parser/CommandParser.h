#include "../command/CommandInterface.h"
#include <memory>

class CommandParser
{
public:
	static std::unique_ptr<CommandInterface> parseString(const std::string& instruction);
};
