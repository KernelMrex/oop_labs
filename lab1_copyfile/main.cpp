#include <iostream>
#include <fstream>
#include <optional>
#include <stdexcept>

struct Args {
    std::string inputPath;
    std::string outputPath;
};

std::optional<Args> ParseArgs(int argc, char **argv) {
    // Validate input values
    if (argc != 3) {
        return std::nullopt;
    }

    // Get filenames
    return {(Args) {argv[1], argv[2]}};
}

void CopyFile(std::ifstream& in, std::ofstream& out) {
    int inputGet;
    while ((inputGet = in.get()) != -1) {
        if (!out.put(inputGet)) {
            break;
        }
    }
    if (in.bad()) {
        throw std::runtime_error("Error while reading file");
    }
    if (!out.flush()) {
        throw std::runtime_error("Error while writing data on drive");
    }
}

int main(int argc, char *argv[]) {
    // Parsing arguments
    std::optional<Args> args = ParseArgs(argc, argv);
    if (!args.has_value()) {
        std::cout << "Invalid args count. Usage copyfile.out <input file> <output file>" << std::endl;
        return 1;
    }

    // Check if input file exists
    std::ifstream inputFile;
    inputFile.open(args->inputPath, std::ios::in | std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "Error '" << args->inputPath << "' file not exists" << std::endl;
        return 1;
    }

    // Check if output file exists
    std::ofstream outputFile;
    outputFile.open(args->outputPath, std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "Error '" << args->outputPath << "' file not exists" << std::endl;
        return 1;
    }

    // Coping files
    try {
        CopyFile(inputFile, outputFile);
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        return 1;
    }

    return 0;
}