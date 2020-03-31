#include "prime_numbers.h"
#include <iostream>

std::optional<int> GetArgs(int argc, char* argv[])
{
	if (argc == 2)
	{
		try
		{
			return { std::stoi(argv[1]) };
		}
		catch (const std::exception&)
		{
			return std::nullopt;
		}
	}
	return std::nullopt;
}

int main(int argc, char* argv[])
{
	auto upperBound = GetArgs(argc, argv);
	if (!upperBound.has_value())
	{
		std::cout << "Bad upper bound number." << std::endl
				  << "Usage: prime <upper_bound>" << std::endl;
		return 1;
	}

	auto primeSet = GeneratePrimeNumbers(upperBound.value());
	for (auto item : primeSet)
	{
		std::cout << item << " ";
	}
	std::cout << std::endl;

	return 0;
}
