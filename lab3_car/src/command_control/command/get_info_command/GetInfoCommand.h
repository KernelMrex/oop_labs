#include "../CommandInterface.h"

class GetInfoCommand : public CommandInterface
{
public:
	Result execute(Car& car) override;
};