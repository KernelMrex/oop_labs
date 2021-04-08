#include "GetInfoCommand.h"
#include <sstream>

Result GetInfoCommand::execute(Car& car)
{
	std::stringstream infoStream;
	infoStream << "Gear: " << car.GetGear() << " Speed: " << car.GetSpeed();
	Result result(true, infoStream.str());
	return result;
}
