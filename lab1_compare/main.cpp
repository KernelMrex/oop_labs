#include <iostream>
#include <fstream>
#include <optional>
#include <stdexcept>

struct Args {
    std::string filePath1;
    std::string filePath2;
};

std::optional<Args> ParseArgs(int argc, char **argv) {
    // Validate input values
    if (argc != 3) {
        return std::nullopt;
    }

    // Get filenames
    return {(Args) {argv[1], argv[2]}};
}

unsigned long CompareStreams(std::istream& in1, std::istream& in2) {
    char bufferChar1, bufferChar2;
    unsigned long amountOfNewLineChars = 1;
    while (in1.get(bufferChar1).good() & in2.get(bufferChar2).good()) {
        if (bufferChar1 != bufferChar2) {
            return amountOfNewLineChars;
        }
        if (bufferChar1 == '\n') {
            amountOfNewLineChars++;
        }
    }

    // Checking EOF
    if (!in1.eof() || !in2.eof()) {
        return amountOfNewLineChars + 1;
    }

    // Checking errors while reading
    if (in1.bad()) {
        throw std::runtime_error("Error while reading first stream");
    }
    if (in2.bad()) {
        throw std::runtime_error("Error while reading second stream");
    }
    return 0;
}

unsigned long CompareFiles(const std::string& filePath1, const std::string& filePath2) {
    // Check if input file exists
    std::ifstream inputFile1;
    inputFile1.open(filePath1);
    if (!inputFile1.is_open()) {
        throw std::runtime_error("Error '" + filePath1 + "' file not exists");
    }

    // Check if input file exists
    std::ifstream inputFile2;
    inputFile2.open(filePath2);
    if (!inputFile2.is_open()) {
        throw std::runtime_error("Error '" + filePath2 + "' file not exists");
    }

    return CompareStreams(inputFile1, inputFile2);
}

int main(int argc, char *argv[]) {
    // Parse args
    std::optional<Args> args = ParseArgs(argc, argv);
    if (!args.has_value()) {
        std::cout << "Invalid arguments amount. Usage compare.out <file1> <file2>" << std::endl;
        return 1;
    }

    // Comparing files
    unsigned long difLine;
    try {
        difLine = CompareFiles(args->filePath1, args->filePath2);
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        return 1;
    }

    // Writing result
    if (difLine) {
        std::cout << "Files are different. Line number is " << difLine << std::endl;
        return 1;
    }
    std::cout << "Files are equal" << std::endl;

    return 0;
}
