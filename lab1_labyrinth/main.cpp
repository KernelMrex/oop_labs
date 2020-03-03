#include <iostream>
#include <optional>
#include <array>

/* Defines */
#define LABYRINTH_MAX_SIZE 3

struct Args {
    std::string inputFilename;
    std::string outputFilename;
};

typedef std::array<std::array<char, LABYRINTH_MAX_SIZE>, LABYRINTH_MAX_SIZE> Labyrinth;

/* Prototypes */
std::optional<Args> parseArgs(int argc, char *argv[]);

// TODO
Labyrinth readLabyrinthFromFile(const std::string& filepath);

/* Main */
int main(int argc, char *argv[]) {
    auto argsOptional = parseArgs(argc, argv);
    if (!argsOptional.has_value()) {
        std::cout << "Bad input arguments" << std::endl;
        std::cout << "Usage: labyrinth <input file> <output file>" << std::endl;
        return 1;
    }

    return 0;
}

/* Functions */
std::optional<Args> parseArgs(int argc, char *argv[]) {
    if (argc != 3) {
        return std::nullopt;
    }
    return {
            (Args) {
                    argv[1],
                    argv[2]
            }
    };
}