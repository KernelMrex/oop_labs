#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <optional>
#include <sstream>
#include <vector>

std::optional<std::vector<double>> ReadVector(std::istream& input);

void PrintVector(const std::vector<double>& vector, std::ostream& output);

std::vector<double> GetMinItemsInVector(std::vector<double> vector, int minItemsAmount);

std::vector<double> AddNumToEachItem(const std::vector<double>& vector, double num);

std::vector<double> AddToEachItemAverageOf3MinNumbers(const std::vector<double>& vector);

int main()
{
	auto vector = ReadVector(std::cin);
	if (!vector.has_value())
	{
		std::cout << "Error while reading vector" << std::endl;
		return 1;
	}

	auto resultVector = AddToEachItemAverageOf3MinNumbers(vector.value());

	PrintVector(resultVector, std::cout);
	return 0;
}

std::optional<std::vector<double>> ReadVector(std::istream& input)
{
	// Get first line of input
	std::string inputString;
	std::getline(input, inputString);
	std::istringstream stringStream(inputString);

	// Reading vector from first string
	std::vector<double> vector;
	double num;
	while (stringStream >> num)
	{
		vector.push_back(num);
	}

	if (!stringStream.eof() || stringStream.bad())
	{
		return std::nullopt;
	}

	return { vector };
}

void PrintVector(const std::vector<double>& vector, std::ostream& output)
{
	for (auto iterator = vector.begin(); iterator != vector.end(); std::advance(iterator, 1))
	{
		output << *iterator << " ";
	}
	output << std::endl;
}

std::vector<double> GetMinItemsInVector(std::vector<double> vector, int minItemsAmount)
{
	std::vector<double> result;
	for (int i = 0; i < minItemsAmount; i++)
	{
		if (vector.empty())
		{
			return vector;
		}
		auto minItem = std::min_element(vector.begin(), vector.end());
		result.push_back(*minItem);
		vector.erase(minItem);
	}
	return result;
}

std::vector<double> AddNumToEachItem(const std::vector<double>& vector, double num)
{
	std::vector<double> result = vector;
	for (auto iterator = result.begin(); iterator != result.end(); std::advance(iterator, 1))
	{
		*iterator += num;
	}
	return result;
}

std::vector<double> AddToEachItemAverageOf3MinNumbers(const std::vector<double>& vector)
{
	auto minItems = GetMinItemsInVector(vector, 3);
	auto average = std::round((std::accumulate(minItems.begin(), minItems.end(), 0.0) / 3) * 1000) / 1000;
	return AddNumToEachItem(vector, average);
}
