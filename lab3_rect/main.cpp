#include "CRectangle.h"
#include <iostream>

int main()
{
	CRectangle rect{1, 1, 3, 4};
	std::cout << rect.GetRight() << std::endl;

	return 0;
}
