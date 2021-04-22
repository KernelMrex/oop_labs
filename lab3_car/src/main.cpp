#include "command_control/CommandControl.h"
#include <iostream>

int main()
{
	Car car;
	CommandControl commandControl(car, std::cin, std::cout);
	commandControl.ListenAndServe();
}