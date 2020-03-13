#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>
#include <iterator>

std::optional<std::vector<double>> ReadVector(std::istream& input);

void PrintVector(const std::vector<double>& vector, std::ostream& output);

std::vector<double> GetMinItemsInVector(std::vector<double> vector, int minItemsAmount);

std::vector<double> AddNumToEachItem(std::vector<double> vector, double num);

std::vector<double> AddToEachItemSumOf3MinNumbers(const std::vector<double>& vector);

int main()
{
	auto vector = ReadVector(std::cin);
	if (!vector.has_value())
	{
		std::cout << "Error while reading vector" << std::endl;
		return 1;
	}

	auto resultVector = AddToEachItemSumOf3MinNumbers(vector.value());

	PrintVector(resultVector, std::cout);
	return 0;
}

std::optional<std::vector<double>> ReadVector(std::istream& input)
{
	std::vector<double> vector(std::istream_iterator<double>(input), (std::istream_iterator<double>()));

	if (!input.eof() || input.bad())
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

std::vector<double> AddNumToEachItem(std::vector<double> vector, double num)
{
	std::transform(vector.begin(), vector.end(), vector.begin(), [num](const double a) {
		return a + num;
	});
	return vector;
}

std::vector<double> AddToEachItemSumOf3MinNumbers(const std::vector<double>& vector)
{
	auto minItems = GetMinItemsInVector(vector, 3);
	auto sum = std::accumulate(minItems.begin(), minItems.end(), 0.0);
	return AddNumToEachItem(vector, sum);
}
