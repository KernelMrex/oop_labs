#include <iostream>
#include <optional>
#include <array>
#include <fstream>

/* Defines */
#define LABYRINTH_MAX_SIZE 5
#define LABYRINTH_CELL_EMPTY 0
#define LABYRINTH_CELL_EOL -1
#define LABYRINTH_CELL_EOF -2
#define LABYRINTH_CELL_NOT_DEFINED -3
#define LABYRINTH_CELL_WALL -4


struct Args {
    std::string inputFilename;
    std::string outputFilename;
};

typedef std::array<std::array<int, LABYRINTH_MAX_SIZE + 1>, LABYRINTH_MAX_SIZE + 1> Labyrinth;

/* Prototypes */
std::optional<Args> ParseArgs(int argc, char *argv[]);

Labyrinth ReadLabyrinthFromFile(const std::string& filepath);

Labyrinth ReadLabyrinth(std::istream& inputStream);

int GetLabyrinthCellByChar(char ch);

char GetLabyrinthCellByInt(int cell);

void PrintLabyrinth(std::ostream& outputStream, const Labyrinth& labyrinth);

/* Main */
int main(int argc, char *argv[]) {
    auto argsOptional = ParseArgs(argc, argv);
    if (!argsOptional.has_value()) {
        std::cout << "Bad input arguments" << std::endl;
        std::cout << "Usage: labyrinth <input file> <output file>" << std::endl;
        return 1;
    }


    Labyrinth labyrinth;
    try {
        labyrinth = ReadLabyrinthFromFile(argsOptional->inputFilename);
    } catch (const std::exception& err) {
        std::cout << "Error while reading labyrinth: " << err.what() << std::endl;
        return 1;
    }

    PrintLabyrinth(std::cout, labyrinth);

    return 0;
}

/* Functions */
std::optional<Args> ParseArgs(int argc, char **argv) {
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

Labyrinth ReadLabyrinthFromFile(const std::string& filepath) {
    std::ifstream inputFile;
    inputFile.open(filepath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("couldn't open file");
    }

    auto labyrinth = ReadLabyrinth(inputFile);

    inputFile.close();

    return labyrinth;
}

//Labyrinth ReadLabyrinth(std::istream& inputStream) {
//    Labyrinth labyrinth;
//    bool isEOF = false;
//    int i;
//    for (i = 0; i < LABYRINTH_MAX_SIZE && !isEOF; i++) {
//        bool isNewLine = false;
//        for (int j = 0; j < LABYRINTH_MAX_SIZE && !isNewLine && !isEOF; j++) {
//            if (inputStream.eof()) {
//                isEOF = true;
//                continue;
//            }
//            char ch;
//            if (!(inputStream >> ch)) {
//                throw std::runtime_error("error while reading labyrinth");
//            }
//            if (ch == '\r') {
//                continue;
//            }
//            if (ch == '\n') {
//                labyrinth[i][j + 1] = LABYRINTH_CELL_EOL;
//                isNewLine = true;
//            }
//            labyrinth[i][j] = GetLabyrinthCellByChar(ch);
//        }
//    }
//    labyrinth[i][0] = LABYRINTH_CELL_EOF;
//    return labyrinth;
//}

Labyrinth ReadLabyrinth(std::istream& inputStream) {
    Labyrinth labyrinth;

    char ch;
    int i = 0;
    int j = 0;
    while (!(inputStream >> ch)) {
        switch (ch) {
            case 'A':
            case 'B':
            case ' ':
                i++;
                labyrinth[i][j] = GetLabyrinthCellByChar(ch);
                break;
            case '\n':
                j++;
                break;
            default:
                throw std::runtime_error("unexpected input");
        }
    }

    if (!inputStream.good()) {
        throw std::runtime_error("error while reading labyrinth");
    }

    return labyrinth;
}


int GetLabyrinthCellByChar(char ch) {
    switch (ch) {
        case ' ':
            return LABYRINTH_CELL_EMPTY;
        case '#':
            return LABYRINTH_CELL_WALL;
        default:
            return LABYRINTH_CELL_NOT_DEFINED;
    }
}

char GetLabyrinthCellByInt(int cell) {
    switch (cell) {
        case LABYRINTH_CELL_EMPTY:
            return ' ';
        case LABYRINTH_CELL_WALL:
            return '#';
        case LABYRINTH_CELL_EOL:
            return '\n';
        default:
            return '%';
    }
}

void PrintLabyrinth(std::ostream& outputStream, const Labyrinth& labyrinth) {
    bool isEOF = false;
    for (int i = 0; i < LABYRINTH_MAX_SIZE && !isEOF; i++) {
        if (labyrinth[i][0] == LABYRINTH_CELL_EOF) {
            isEOF = true;
            continue;
        }
        bool isEOL = false;
        for (int j = 0; j < LABYRINTH_MAX_SIZE && !isEOL; j++) {
            if (labyrinth[i][j] == LABYRINTH_CELL_EOL) {
                isEOL = true;
            }
            outputStream << "[" << GetLabyrinthCellByInt(labyrinth[i][j]) << "]";
        }
        outputStream << std::endl;
    }
}
