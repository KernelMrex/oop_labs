#include "command_control/CommandControl.h"
#include <iostream>

int main()
{
	Car car;
	CommandControl commandControl(car);

	commandControl.ListenAndServe(std::cin, std::cout);
}