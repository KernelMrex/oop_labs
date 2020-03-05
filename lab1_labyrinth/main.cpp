#include <iostream>
#include <optional>
#include <array>
#include <fstream>
#include <queue>
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
#define LABYRINTH_CELL_WAY -7


typedef int CellType;

typedef std::array<std::array<int, LABYRINTH_MAX_SIZE + 1>, LABYRINTH_MAX_SIZE + 1> Labyrinth;

typedef std::pair<int, int> CellCoordinates;

struct Cell {
	CellCoordinates coordinates;
	int value{};
};

struct Args {
	std::string inputFilename;
	std::string outputFilename;
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

void SpreadWave(std::queue<Cell>& queue, const Cell& waveCell);

std::optional<Labyrinth> CalculateWay(const Labyrinth& labyrinth);

std::optional<CellCoordinates> SearchNextNeighbour(const Labyrinth& labyrinth, const CellCoordinates& curCell);

std::optional<Cell> GetCell(const Labyrinth& labyrinth, int x, int y);

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

	auto resultLabyrinth = CalculateWay(labyrinth);
	if (!resultLabyrinth.has_value()) {
		std::cout << "Error while searching fastest way: malformed labyrinth" << std::endl;
		return 1;
	}
	PrintLabyrinth(std::cout, resultLabyrinth.value());

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
	labyrinth[i][j] = LABYRINTH_CELL_EOL;
	labyrinth[i + 1][0] = LABYRINTH_CELL_EOF;

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
		case LABYRINTH_CELL_WAY:
			return '*';
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
	std::queue<Cell> waveQueue;

	// Find labyrinth start
	auto startCoordinatesOptional = FindFirstCellOfType(labyrinth, LABYRINTH_CELL_START);
	if (!startCoordinatesOptional.has_value()) {
		throw std::runtime_error("malformed labyrinth");
	}
	waveQueue.push((Cell) {
		startCoordinatesOptional.value(),
		0
	});

	// Wave fill
	while (!waveQueue.empty()) {
		auto waveCell = waveQueue.front();
		waveQueue.pop();

		int labyrinthCellValue = labyrinth[waveCell.coordinates.first][waveCell.coordinates.second];
		if (labyrinthCellValue == LABYRINTH_CELL_STOP) {
			break;
		}
		if (labyrinthCellValue == LABYRINTH_CELL_START) {
			SpreadWave(waveQueue, waveCell);
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

std::optional<CellCoordinates> FindFirstCellOfType(const Labyrinth& labyrinth, CellType cellType) {
	for (int i = 0; i < LABYRINTH_MAX_SIZE; i++) {
		bool isEOL = false;
		for (int j = 0; j < LABYRINTH_MAX_SIZE && !isEOL; j++) {
			isEOL = (labyrinth[i][j] == LABYRINTH_CELL_EOL);
			if (labyrinth[i][j] == cellType) {
				return {CellCoordinates(i, j)};
			}
		}
	}
	return std::nullopt;
}

void SpreadWave(std::queue<Cell>& queue, const Cell& waveCell) {
	if (waveCell.coordinates.first - 1 >= 0) {
		queue.push((Cell) {
			CellCoordinates(waveCell.coordinates.first - 1, waveCell.coordinates.second),
			waveCell.value + 1
		});
	}
	if (waveCell.coordinates.second - 1 >= 0) {
		queue.push((Cell) {
			CellCoordinates(waveCell.coordinates.first, waveCell.coordinates.second - 1),
			waveCell.value + 1
		});
	}
	if (waveCell.coordinates.first + 1 < LABYRINTH_MAX_SIZE) {
		queue.push((Cell) {
			CellCoordinates(waveCell.coordinates.first + 1, waveCell.coordinates.second),
			waveCell.value + 1
		});
	}
	if (waveCell.coordinates.second + 1 < LABYRINTH_MAX_SIZE) {
		queue.push((Cell) {
			CellCoordinates(waveCell.coordinates.first, waveCell.coordinates.second + 1),
			waveCell.value + 1
		});
	}
}

std::optional<Labyrinth> CalculateWay(const Labyrinth& labyrinth) {
	Labyrinth wavedLabyrinth = LabyrinthWaveFill(labyrinth);
	Labyrinth result = labyrinth;

	// Searching for exit
	auto exitCellCoordinates = FindFirstCellOfType(wavedLabyrinth, LABYRINTH_CELL_STOP);
	if (!exitCellCoordinates.has_value()) {
		return std::nullopt;
	}

	CellCoordinates currentCell = exitCellCoordinates.value();

	while (true) {
		auto nextCell = SearchNextNeighbour(wavedLabyrinth, currentCell);
		if (!nextCell.has_value()) {
			return std::nullopt;
		}

		if (result[nextCell->first][nextCell->second] == LABYRINTH_CELL_START) {
			return result;
		}
		result[nextCell->first][nextCell->second] = LABYRINTH_CELL_WAY;

		currentCell = nextCell.value();
	}
}

std::optional<CellCoordinates> SearchNextNeighbour(const Labyrinth& labyrinth, const CellCoordinates& curCell) {
	Cell minCell;
	bool isMinFound = false;

	// Upper
	auto upperCell = GetCell(labyrinth, curCell.first - 1, curCell.second);
	if (upperCell.has_value() && (upperCell->value > 0 || upperCell->value == LABYRINTH_CELL_START)) {
		minCell = upperCell.value();
		isMinFound = true;
	}

	// Right
	auto rightCell = GetCell(labyrinth, curCell.first, curCell.second + 1);
	if (rightCell.has_value() && (rightCell->value > 0 || rightCell->value == LABYRINTH_CELL_START)) {
		if (!isMinFound) {
			minCell = rightCell.value();
			isMinFound = true;
		} else {
			if (rightCell->value < minCell.value) {
				minCell = rightCell.value();
			}
		}
	}

	// Lower
	auto lowerCell = GetCell(labyrinth, curCell.first + 1, curCell.second);
	if (lowerCell.has_value() && (lowerCell->value > 0 || lowerCell->value == LABYRINTH_CELL_START)) {
		if (!isMinFound) {
			minCell = lowerCell.value();
			isMinFound = true;
		} else {
			if (lowerCell->value < minCell.value) {
				minCell = lowerCell.value();
			}
		}
	}

	// Left
	auto leftCell = GetCell(labyrinth, curCell.first, curCell.second - 1);
	if (leftCell.has_value() && (leftCell->value > 0 || leftCell->value == LABYRINTH_CELL_START)) {
		if (!isMinFound) {
			minCell = leftCell.value();
			isMinFound = true;
		} else {
			if (leftCell->value < minCell.value) {
				minCell = leftCell.value();
			}
		}
	}

	if (isMinFound) {
		return minCell.coordinates;
	}
	return std::nullopt;
}

std::optional<Cell> GetCell(const Labyrinth& labyrinth, int x, int y) {
	if (x >= LABYRINTH_MAX_SIZE || x < 0) {
		return std::nullopt;
	}
	if (y >= LABYRINTH_MAX_SIZE || y < 0) {
		return std::nullopt;
	}
	return {(Cell) {
		CellCoordinates(x, y),
		labyrinth[x][y]
	}};
}