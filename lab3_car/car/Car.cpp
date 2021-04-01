#include "Car.h"

Car::Car()
	: gear(0)
	, speed(0)
	, engineOn(false)
{
}

bool Car::IsEngineTurnOn() const
{
	return engineOn;
}

Direction Car::GetDirection() const
{
	if (speed > 0)
	{
		return Direction::FORWARD;
	}
	else if (speed < 0)
	{
		return Direction::BACKWARD;
	}
	else
	{
		return Direction::STILL;
	}
}

int Car::GetSpeed() const
{
	return (speed > 0) ? speed : -speed;
}

int Car::GetGear() const
{
	return gear;
}

bool Car::TurnEngineOn()
{
	return engineOn = true;
}

bool Car::TurnEngineOff()
{
	if (GetSpeed() != 0 || GetGear() != 0)
	{
		return false;
	}
	engineOn = false;
	return true;
}

bool Car::SetGear(int newGear)
{
	if (!IsValidGearChange(newGear) || !IsEngineTurnOn())
	{
		return false;
	}

	gear = newGear;
	return true;
}

bool Car::SetSpeed(int newSpeed)
{
	if (newSpeed < 0 || !IsEngineTurnOn())
	{
		return false;
	}

	if (GetGear() == -1 || GetDirection() == Direction::BACKWARD)
	{
		newSpeed = -newSpeed;
	}

	if (!IsValidSpeedChange(newSpeed))
	{
		return false;
	}

	speed = newSpeed;
	return true;
}

bool Car::IsValidGearChange(int newGear) const
{
	switch (newGear)
	{
	case -1:
		return speed == 0;
	case 0:
		return true;
	case 1:
		return speed >= 0 && speed <= 30;
	case 2:
		return speed >= 20 && speed <= 50;
	case 3:
		return speed >= 30 && speed <= 60;
	case 4:
		return speed >= 40 && speed <= 90;
	case 5:
		return speed >= 50 && speed <= 150;
	default:
		return false;
	}
}

bool Car::IsValidSpeedChange(int newSpeed) const
{
	switch (gear)
	{
	case -1:
		return newSpeed >= -20 && newSpeed <= 0;
	case 0:
		return (newSpeed <= speed && GetDirection() == Direction::FORWARD) || (newSpeed >= speed && GetDirection() == Direction::BACKWARD) || newSpeed == 0;
	case 1:
		return newSpeed >= 0 && newSpeed <= 30;
	case 2:
		return newSpeed >= 20 && newSpeed <= 50;
	case 3:
		return newSpeed >= 30 && newSpeed <= 60;
	case 4:
		return newSpeed >= 40 && newSpeed <= 90;
	case 5:
		return newSpeed >= 50 && newSpeed <= 150;
	default:
		return false;
	}
}
