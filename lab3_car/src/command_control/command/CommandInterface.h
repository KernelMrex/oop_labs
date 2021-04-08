#include "../../car/Car.h"
#include "../result/Result.h"

class CommandInterface
{
public:
	virtual Result execute(Car& car) = 0;

	virtual ~CommandInterface() = default;
};
