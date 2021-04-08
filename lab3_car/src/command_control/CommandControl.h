#include "../car/Car.h"
#include "command_parser/CommandParser.h"
#include <istream>

class CommandControl
{
public:
	explicit CommandControl(Car& car);

	void ListenAndServe(std::istream& in, std::ostream& out) const;

private:
	Car& car;
};
