#include <algorithm>
#include <iostream>
#include "vector_functions.h"

int main()
{
    try {
        ReadAndAddToEachItemSumOf3MinNumbers(std::cin, std::cout);
    } catch (const std::exception& err) {
        std::cout << err.what() << std::endl;
        return 1;
    }

	return 0;
}