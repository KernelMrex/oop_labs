#include <optional>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>

#include "vector_functions.h"

void ReadAndAddToEachItemSumOf3MinNumbers(std::istream& in, std::ostream& out) {
    auto vector = ReadVector(in);
    if (!vector.has_value())
    {
        throw std::runtime_error("Error while reading vector");
    }
    auto resultVector = AddToEachItemSumOf3MinNumbers(vector.value());
    std::sort(resultVector.begin(), resultVector.end());
    PrintVector(resultVector, out);
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
    std::partial_sort(vector.begin(), vector.end(), vector.end());
    auto iterTo = vector.begin();
    std::advance(iterTo, minItemsAmount);
    return std::vector(vector.begin(), iterTo);
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

