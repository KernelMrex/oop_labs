#include <optional>
#include <vector>

void ReadAndAddToEachItemSumOf3MinNumbers(std::istream& in, std::ostream& out);

std::optional<std::vector<double>> ReadVector(std::istream& input);

void PrintVector(const std::vector<double>& vector, std::ostream& output);

std::vector<double> GetMinItemsInVector(std::vector<double> vector, int minItemsAmount);

std::vector<double> AddNumToEachItem(std::vector<double> vector, double num);

std::vector<double> AddToEachItemSumOf3MinNumbers(const std::vector<double>& vector);
