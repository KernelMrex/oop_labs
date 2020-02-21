#include <iostream>
#include <optional>
#include <fstream>

#define MATRIX_SIZE 3

struct Args {
    std::string filepath;
};

typedef double Matrix[MATRIX_SIZE][MATRIX_SIZE];


std::optional<Args> ParseArgs(int argc, char *argv[]);

void ReadMatrixFromFile(const std::string &filepath, Matrix &matrix);

void ReadMatrix(std::istream &in, Matrix &matrix);

long double CalcMatrixDeterminant(Matrix &matrix);

void PrintMatrix(std::ostream &out, Matrix &matrix);

int main(int argc, char *argv[]) {
    // Parsing arguments
    auto args = ParseArgs(argc, argv);
    if (!args.has_value()) {
        std::cout << "Error: wrong amount of arguments" << std::endl;
        std::cout << "Usage: invert <matrix file path>" << std::endl;
        return 1;
    }

    // Reading matrix
    Matrix matrix = {};
    try {
        ReadMatrixFromFile(args->filepath, matrix);
    } catch (std::exception &err) {
        std::cout << err.what() << std::endl;
        return 1;
    }

    // Calculating invert matrix
    long double matrixDeterminant = CalcMatrixDeterminant(matrix);
    if (matrixDeterminant == 0) {
        std::cout << "Invert matrix not exists" << std::endl;
        return 1;
    }

    // TODO: ...

    return 0;
}


std::optional<Args> ParseArgs(int argc, char *argv[]) {
    if (argc != 2) {
        return std::nullopt;
    }
    return {(Args) {argv[1]}};
}

void ReadMatrixFromFile(const std::string &filepath, Matrix &matrix) {
    std::ifstream file;

    std::cout << filepath << std::endl;

    file.open(filepath, std::ios::in);
    if (!file.is_open()) {
        throw std::runtime_error("cannot open file '" + filepath + "'");
    }
    ReadMatrix(file, matrix);
}

void ReadMatrix(std::istream &in, Matrix &matrix) {
    for (auto &matrixRow : matrix) {
        for (double &matrixField : matrixRow) {
            if (!(in >> matrixField)) {
                throw std::runtime_error("");
            }
        }
    }
}

long double CalcMatrixDeterminant(Matrix &matrix) {
    return
            matrix[0][0] * matrix[1][1] * matrix[2][2]
            + matrix[0][2] * matrix[1][0] * matrix[2][1]
            + matrix[0][1] * matrix[1][2] * matrix[2][0]
            - matrix[0][2] * matrix[1][1] * matrix[2][0]
            - matrix[0][0] * matrix[1][2] * matrix[2][1]
            - matrix[0][1] * matrix[1][0] * matrix[2][2];
}

void PrintMatrix(std::ostream &out, Matrix &matrix) {
    for (auto &matrixRow : matrix) {
        for (double &matrixField : matrixRow) {
            out << matrixField << " ";
        }
        out << std::endl;
    }
}