#include <iostream>
#include <optional>
#include <array>
#include <fstream>
#include <queue>
#include <tuple>
#include <iomanip>

/* Defines */
#define LABYRINTH_MAX_SIZE 12
#define LABYRINTH_CELL_EMPTY 0
#define LABYRINTH_CELL_EOL -1
#define LABYRINTH_CELL_EOF -2
#define LABYRINTH_CELL_NOT_DEFINED -3
#define LABYRINTH_CELL_WALL -4
#define LABYRINTH_CELL_START -5
#define LABYRINTH_CELL_STOP -6


struct Args {
    std::string inputFilename;
    std::string outputFilename;
};

typedef std::array<std::array<int, LABYRINTH_MAX_SIZE + 1>, LABYRINTH_MAX_SIZE + 1> Labyrinth;

typedef int CellType;

struct WaveCell {
    std::pair<int, int> coordinates;
    int value;
};

/* Prototypes */
std::optional<Args> ParseArgs(int argc, char *argv[]);

Labyrinth ReadLabyrinthFromFile(const std::string& filepath);

Labyrinth ReadLabyrinth(std::istream& inputStream);

int GetLabyrinthCellByChar(char ch);

char GetLabyrinthCellByInt(int cell);

void PrintLabyrinth(std::ostream& outputStream, const Labyrinth& labyrinth);

Labyrinth LabyrinthWaveFill(Labyrinth labyrinth);

std::optional<std::pair<int, int>> FindFirstCellOfType(const Labyrinth& labyrinth, CellType cellType);

void SpreadWave(std::queue<WaveCell>& queue, const WaveCell& waveCell);

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

    Labyrinth wavedLabyrinth;
    wavedLabyrinth = LabyrinthWaveFill(labyrinth);

    PrintLabyrinth(std::cout, wavedLabyrinth);

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
    inputFile.open(filepath, std::ios::in | std::ios::binary);
    if (!inputFile.is_open() || !inputFile.good()) {
        throw std::runtime_error("couldn't open file");
    }

    auto labyrinth = ReadLabyrinth(inputFile);

    inputFile.close();

    return labyrinth;
}

Labyrinth ReadLabyrinth(std::istream& inputStream) {
    Labyrinth labyrinth;

    char ch;
    int i = 0;
    int j = 0;
    while (inputStream >> std::noskipws >> ch) {
        switch (ch) {
            case 'A':
            case 'B':
            case '#':
            case ' ':
                labyrinth[i][j] = GetLabyrinthCellByChar(ch);
                j++;
                break;
            case '\n':
                labyrinth[i][j] = GetLabyrinthCellByChar(ch);
                j = 0;
                i++;
                break;
            default:
                throw std::runtime_error("unexpected input");
        }
    }
    labyrinth[i][0] = LABYRINTH_CELL_EOF;

    if (inputStream.bad()) {
        throw std::runtime_error("error while reading labyrinth");
    }

    return labyrinth;
}


int GetLabyrinthCellByChar(char ch) {
    switch (ch) {
        case ' ':
            return LABYRINTH_CELL_EMPTY;
        case '\n':
            return LABYRINTH_CELL_EOL;
        case '#':
            return LABYRINTH_CELL_WALL;
        case 'A':
            return LABYRINTH_CELL_START;
        case 'B':
            return LABYRINTH_CELL_STOP;
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
        case LABYRINTH_CELL_START:
            return 'A';
        case LABYRINTH_CELL_STOP:
            return 'B';
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
                continue;
            }
            if (labyrinth[i][j] > 0) {
                outputStream << std::setw(3) << labyrinth[i][j];
            } else {
                outputStream << std::setw(3) << GetLabyrinthCellByInt(labyrinth[i][j]);
            }
        }
        outputStream << std::endl;
    }
}

Labyrinth LabyrinthWaveFill(Labyrinth labyrinth) {
    std::queue<WaveCell> waveQueue;

    // Find labyrinth start
    auto startCoordinatesOptional = FindFirstCellOfType(labyrinth, LABYRINTH_CELL_START);
    if (!startCoordinatesOptional.has_value()) {
        throw std::runtime_error("malformed labyrinth");
    }
    labyrinth[startCoordinatesOptional->first][startCoordinatesOptional->second] = 0;
    waveQueue.push((WaveCell) {
            startCoordinatesOptional.value(),
            1
    });

    // Wave fill
    while (!waveQueue.empty()) {
        auto waveCell = waveQueue.front();
        waveQueue.pop();

        std::cout <<  waveCell.coordinates.first << " " << waveCell.coordinates.second << " : " << labyrinth[waveCell.coordinates.first][waveCell.coordinates.second] << std::endl;
        int labyrinthCellValue = labyrinth[waveCell.coordinates.first][waveCell.coordinates.second];
        if (labyrinthCellValue == LABYRINTH_CELL_STOP) {
            break;
        }
        if (labyrinthCellValue == LABYRINTH_CELL_WALL) {
            continue;
        }
        if (labyrinthCellValue == LABYRINTH_CELL_EMPTY) {
            labyrinth[waveCell.coordinates.first][waveCell.coordinates.second] = waveCell.value;
            SpreadWave(waveQueue, waveCell);
        }
    }
    return labyrinth;
}

std::optional<std::pair<int, int>> FindFirstCellOfType(const Labyrinth& labyrinth, CellType cellType) {
    for (int i = 0; i < LABYRINTH_MAX_SIZE; i++) {
        bool isEOL = false;
        for (int j = 0; j < LABYRINTH_MAX_SIZE && !isEOL; j++) {
            isEOL = (labyrinth[i][j] == LABYRINTH_CELL_EOL);
            if (labyrinth[i][j] == cellType) {
                return {std::pair<int, int>(i, j)};
            }
        }
    }
    return std::nullopt;
}

void SpreadWave(std::queue<WaveCell>& queue, const WaveCell& waveCell) {
    if (waveCell.coordinates.first - 1 >= 0) {
        queue.push((WaveCell) {
                std::pair<int, int>(waveCell.coordinates.first - 1, waveCell.coordinates.second),
                waveCell.value + 1
        });
    }
    if (waveCell.coordinates.second - 1 >= 0) {
        queue.push((WaveCell) {
                std::pair<int, int>(waveCell.coordinates.first, waveCell.coordinates.second - 1),
                waveCell.value + 1
        });
    }
    if (waveCell.coordinates.first + 1 < LABYRINTH_MAX_SIZE) {
        queue.push((WaveCell) {
                std::pair<int, int>(waveCell.coordinates.first + 1, waveCell.coordinates.second),
                waveCell.value + 1
        });
    }
    if (waveCell.coordinates.second + 1 < LABYRINTH_MAX_SIZE) {
        queue.push((WaveCell) {
                std::pair<int, int>(waveCell.coordinates.first, waveCell.coordinates.second + 1),
                waveCell.value + 1
        });
    }
}