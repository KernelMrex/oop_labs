#include <iostream>
#include <vector>
#include <optional>
#include <sstream>

std::optional<std::vector<double>> ReadVector(std::istream& input);

void PrintVector(const std::vector<double>& vector, std::ostream& output);

int main() {
    auto vector = ReadVector(std::cin);
    if (!vector.has_value()) {
        std::cout << "Error while reading vector" << std::endl;
        return 1;
    }

    PrintVector(vector.value(), std::cout);
    return 0;
}

std::optional<std::vector<double>> ReadVector(std::istream& input) {
    // Get first line of input
    std::string inputString;
    std::getline(input, inputString);
    std::istringstream stringStream(inputString);

    // Reading vector from first string
    std::vector<double> vector;
    double num;
    while (stringStream >> num) {
        vector.push_back(num);
    }
    if (stringStream.fail()) {
        return std::nullopt;
    }

    return {vector};
}

void PrintVector(const std::vector<double>& vector, std::ostream& output) {
    for (auto iterator = vector.begin(); iterator != vector.end(); std::advance(iterator, 1)) {
        output << *iterator << " ";
    }
    output << std::endl;
}
