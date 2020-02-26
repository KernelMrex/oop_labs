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

void ReadMatrixFromFile(const std::string& filepath, Matrix3x3& matrix);

void ReadMatrix(std::istream& in, Matrix3x3& matrix);

void DivideMatrix(const Matrix3x3& matrix, double divisor, Matrix3x3& resultMatrix);

void PrintMatrix(std::ostream& out, Matrix3x3& matrix);

double CalcMatrixDeterminant(const Matrix3x3& matrix);

void CalcAlgebraicComplementMatrix(const Matrix3x3& matrix, Matrix3x3& algebraicComplementMatrix);

void CalcTransposedMatrix(const Matrix3x3& matrix, Matrix3x3& transposedMatrix);

void CalcInvertMatrix(const Matrix3x3& matrix, Matrix3x3& invertMatrix);

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
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        return 1;
    }

    // Calculating invert matrix
    Matrix3x3 invertMatrix = {};
    CalcInvertMatrix(matrix, invertMatrix);

    // Writing matrix
    PrintMatrix(std::cout, invertMatrix);

    return 0;
}

std::optional<Args> ParseArgs(int argc, char *argv[]) {
    if (argc != 2) {
        return std::nullopt;
    }
    return {(Args) {argv[1]}};
}

void ReadMatrixFromFile(const std::string& filepath, Matrix3x3& matrix) {
    std::ifstream file;
    std::cout << filepath << std::endl;
    file.open(filepath, std::ios::in);
    if (!file.is_open()) {
        throw std::runtime_error("cannot open file '" + filepath + "'");
    }
    ReadMatrix(file, matrix);
}

void ReadMatrix(std::istream& in, Matrix3x3& matrix) {
    for (auto& matrixRow : matrix) {
        for (double& matrixField : matrixRow) {
            if (!(in >> matrixField)) {
                throw std::runtime_error("error while reading matrix");
            }
        }
    }
}

void PrintMatrix(std::ostream& out, Matrix3x3& matrix) {
    for (auto& matrixRow : matrix) {
        for (double& matrixField : matrixRow) {
            out << matrixField << " ";
        }
        out << std::endl;
    }
}

void DivideMatrix(const Matrix3x3& matrix, double divisor, Matrix3x3& resultMatrix) {
    for (int i = 0; i < MATRIX_3x3_SIZE; i++) {
        for (int j = 0; j < MATRIX_3x3_SIZE; j++) {
            resultMatrix[i][j] = matrix[i][j] / divisor;
        }
    }
}

double CalcMatrixDeterminant(const Matrix3x3& matrix) {
    return
            matrix[0][0] * matrix[1][1] * matrix[2][2]
            + matrix[0][2] * matrix[1][0] * matrix[2][1]
            + matrix[0][1] * matrix[1][2] * matrix[2][0]
            - matrix[0][2] * matrix[1][1] * matrix[2][0]
            - matrix[0][0] * matrix[1][2] * matrix[2][1]
            - matrix[0][1] * matrix[1][0] * matrix[2][2];
}

void CalcAlgebraicComplementMatrix(const Matrix3x3& matrix, Matrix3x3& algebraicComplementMatrix) {
    for (int i = 0; i < MATRIX_3x3_SIZE; i++) {
        for (int j = 0; j < MATRIX_3x3_SIZE; j++) {
            double minor = matrix[i][j] * matrix[(i + 1) % 3][(j + 1) % 3]
                           - matrix[(i + 1) % 3][j] * matrix[i][(j + 1) % 3];
            algebraicComplementMatrix[(i + 2) % 3][(j + 2) % 3] = minor;
        }
    }
}

void CalcTransposedMatrix(const Matrix3x3& matrix, Matrix3x3& transposedMatrix) {
    for (int i = 0; i < MATRIX_3x3_SIZE; i++) {
        for (int j = i; j < MATRIX_3x3_SIZE; j++) {
            transposedMatrix[j][i] = matrix[i][j];
            transposedMatrix[i][j] = matrix[j][i];
        }
    }
}

void CalcInvertMatrix(const Matrix3x3& matrix, Matrix3x3& invertMatrix) {
    // Calculating matrix determinant
    double matrixDeterminant = CalcMatrixDeterminant(matrix);
    if (matrixDeterminant == 0) {
        throw std::logic_error("Invert matrix not exists");
    }

    // Calculating algebraic complement matrix
    Matrix3x3 algebraicComplementMatrix = {};
    CalcAlgebraicComplementMatrix(matrix, algebraicComplementMatrix);

    // Calculating transposed matrix
    Matrix3x3 transposedMatrix = {};
    CalcTransposedMatrix(algebraicComplementMatrix, transposedMatrix);

    // Calculating result
    DivideMatrix(transposedMatrix, matrixDeterminant, invertMatrix);
}
