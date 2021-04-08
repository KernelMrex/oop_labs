#include "../CommandInterface.h"

class ChangeGearCommand : public CommandInterface
{
public:
	Result execute(Car& car) override;

private:
	int newGear;
};
