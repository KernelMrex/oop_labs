#include "direction/Direction.h"

class Car
{
public:
	Car();

	[[nodiscard]] bool IsEngineTurnOn() const;

	[[nodiscard]] Direction GetDirection() const;

	[[nodiscard]] int GetSpeed() const;

	[[nodiscard]] int GetGear() const;

	bool TurnEngineOn();

	bool TurnEngineOff();

	bool SetGear(int newGear);

	bool SetSpeed(int newSpeed);

private:
	bool engineOn;
	int gear;
	int speed;

	[[nodiscard]] bool IsValidGearChange(int newGear) const;

	[[nodiscard]] bool IsValidSpeedChange(int newSpeed) const;
};