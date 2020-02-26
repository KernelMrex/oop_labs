#include <iostream>
#include <optional>
#include <fstream>

#define MATRIX_3x3_SIZE 3
#define MATRIX_2x2_SIZE 2

struct Args {
    std::string filepath;
};

typedef double Matrix3x3[MATRIX_3x3_SIZE][MATRIX_3x3_SIZE];

typedef double Matrix2x2[MATRIX_2x2_SIZE][MATRIX_2x2_SIZE];


std::optional<Args> ParseArgs(int argc, char *argv[]);

void ReadMatrixFromFile(const std::string &filepath, Matrix3x3 &matrix);

void ReadMatrix(std::istream &in, Matrix3x3 &matrix);

long double CalcMatrixDeterminant(Matrix3x3 &matrix);

void PrintMatrix(std::ostream &out, Matrix3x3 &matrix);

void CalcAlgebraicComplementMatrix(const Matrix3x3 &matrix, Matrix3x3 &minorsMatrix);

int main(int argc, char *argv[]) {
    // Parsing arguments
    auto args = ParseArgs(argc, argv);
    if (!args.has_value()) {
        std::cout << "Error: wrong amount of arguments" << std::endl;
        std::cout << "Usage: invert <matrix file path>" << std::endl;
        return 1;
    }

    // Reading matrix
    Matrix3x3 matrix = {};
    try {
        ReadMatrixFromFile(args->filepath, matrix);
    } catch (std::exception &err) {
        std::cout << err.what() << std::endl;
        return 1;
    }

    // Calculating matrix determinant
    long double matrixDeterminant = CalcMatrixDeterminant(matrix);
    if (matrixDeterminant == 0) {
        std::cout << "Invert matrix not exists" << std::endl;
        return 1;
    }

    // Calculating minors
    Matrix3x3 minorsMatrix = {};
    CalcAlgebraicComplementMatrix(matrix, minorsMatrix);

    // TODO: ...
    PrintMatrix(std::cout, matrix);

    std::cout << std::endl;

    PrintMatrix(std::cout, minorsMatrix);

    return 0;
}


std::optional<Args> ParseArgs(int argc, char *argv[]) {
    if (argc != 2) {
        return std::nullopt;
    }
    return {(Args) {argv[1]}};
}

void ReadMatrixFromFile(const std::string &filepath, Matrix3x3 &matrix) {
    std::ifstream file;

    std::cout << filepath << std::endl;

    file.open(filepath, std::ios::in);
    if (!file.is_open()) {
        throw std::runtime_error("cannot open file '" + filepath + "'");
    }
    ReadMatrix(file, matrix);
}

void ReadMatrix(std::istream &in, Matrix3x3 &matrix) {
    for (auto &matrixRow : matrix) {
        for (double &matrixField : matrixRow) {
            if (!(in >> matrixField)) {
                throw std::runtime_error("error while reading matrix");
            }
        }
    }
}

long double CalcMatrixDeterminant(Matrix3x3 &matrix) {
    return
            matrix[0][0] * matrix[1][1] * matrix[2][2]
            + matrix[0][2] * matrix[1][0] * matrix[2][1]
            + matrix[0][1] * matrix[1][2] * matrix[2][0]
            - matrix[0][2] * matrix[1][1] * matrix[2][0]
            - matrix[0][0] * matrix[1][2] * matrix[2][1]
            - matrix[0][1] * matrix[1][0] * matrix[2][2];
}

void PrintMatrix(std::ostream &out, Matrix3x3 &matrix) {
    for (auto &matrixRow : matrix) {
        for (double &matrixField : matrixRow) {
            out << matrixField << " ";
        }
        out << std::endl;
    }
}

void CalcAlgebraicComplementMatrix(const Matrix3x3 &matrix, Matrix3x3 &minorsMatrix) {
    for (int i = 0; i < MATRIX_3x3_SIZE; i++) {
        for (int j = 0; j < MATRIX_3x3_SIZE; j++) {
            double minor = matrix[i][j] * matrix[(i + 1) % 3][(j + 1) % 3]
                                - matrix[(i + 1) % 3][j] * matrix[i][(j + 1) % 3];
            minorsMatrix[(i + 2) % 3][(j + 2) % 3] = minor;
        }
    }
}
