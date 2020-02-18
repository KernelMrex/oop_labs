#include <cmath>
#include <iostream>
#include <optional>
#include <string>
#include <algorithm>

#define MAX_RADIX 36
#define MIN_RADIX 2

/* Headers */
bool IsCapitalLetter(char ch);

bool IsDigit(char ch);

uint8_t CharToIntRadix(char ch, uint8_t radix);

char IntToCharRadix(uint8_t n, uint8_t radix);

long StringToInt(const std::string &str, uint8_t radix);

std::string IntToString(long n, uint8_t radix);

/* Main logic */
struct Args {
    std::uint8_t sourceNotation;
    std::uint8_t destinationNotation;
    std::string value;
};

std::optional<Args> ParseArgs(int argc, char *argv[]) {
    // Validate input values
    if (argc != 4) {
        return std::nullopt;
    }

    long sourceNotation = StringToInt(argv[1], 10);
    if ((sourceNotation > MAX_RADIX) || (sourceNotation < MIN_RADIX)) {
        throw std::runtime_error("bad range for source notation");
    }

    long destinationNotation = StringToInt(argv[2], 10);
    if ((destinationNotation > MAX_RADIX) || (destinationNotation < MIN_RADIX)) {
        throw std::runtime_error("bad range for destination notation");
    }

    return {
            (Args) {
                    static_cast<uint8_t>(sourceNotation),
                    static_cast<uint8_t>(destinationNotation),
                    argv[3]
            }
    };
}

int main(int argc, char *argv[]) {
    try {
        std::optional<Args> result = ParseArgs(argc, argv);
        if (!result.has_value()) {
            std::cout << "Wrong amount of parameters" << std::endl;
            std::cout << "Usage: radix <source notation> <destination notation> <value>" << std::endl;
            return 1;
        }
        long decimalNumberView = StringToInt(result->value, result->sourceNotation);
        std::cout << IntToString(decimalNumberView, result->destinationNotation) << std::endl;
    } catch (std::exception &err) {
        std::cout << err.what() << std::endl;
        return 1;
    }
    return 0;
}

/* Functions */
bool IsCapitalLetter(char ch) {
    return (ch <= 'Z') && (ch >= 'A');
}

bool IsDigit(char ch) {
    return (ch >= '0') && (ch <= '9');
}

uint8_t CharToIntRadix(char ch, uint8_t radix) {
    if (IsDigit(ch)) {
        if (ch - '0' >= radix) {
            throw std::logic_error("char is bigger than radix");
        }
        return ch - '0';
    }

    if (IsCapitalLetter(ch)) {
        if (ch - 'A' + 10 >= radix) {
            throw std::logic_error("char is bigger than radix");
        }
        return ch - 'A' + 10;
    }

    throw std::logic_error("can not covert char to int");
}

long StringToInt(const std::string &str, uint8_t radix) {
    if ((radix > MAX_RADIX) || (radix < MIN_RADIX)) {
        throw std::runtime_error("radix is not in correct range");
    }

    bool isNegative = false;
    if (str.length() > 0 && str[0] == '-') {
        isNegative = true;
    }

    long result = 0;
    int offset = 0;
    for (int i = (int) str.length() - 1; i >= 0; i--) {
        if (i == 0 && isNegative) {
            result *= -1;
            continue;
        }
        result = result + ((long) pow(radix, offset)) * CharToIntRadix(str[i], radix);
        offset++;
    }

    return result;
}

char IntToCharRadix(uint8_t n, uint8_t radix) {
    if ((radix > MAX_RADIX) || (radix < MIN_RADIX)) {
        throw std::runtime_error("radix is not in correct range");
    }

    if (n >= radix) {
        throw std::runtime_error("number is bigger than radix");
    }

    if ((n >= 0) && (n < 9)) {
        return static_cast<char>('0' + n);
    }

    if ((n >= 10) && (n < 36)) {
        return static_cast<char>('A' + n);
    }

    throw std::runtime_error("number is not in correct range");
}

std::string IntToString(long n, uint8_t radix) {
    if (n == 0) {
        return "0";
    }

    bool isNegative = false;
    if (n < 0) {
        n = -n;
        isNegative = true;
    }

    std::string result = "";
    long divResult;
    while (n > 0) {
        divResult = (n / radix);
        result += IntToCharRadix(n - (divResult * radix), radix);
        n = divResult;
    }

    if (isNegative) {
        result += '-';
    }

    std::reverse(result.begin(), result.end());
    return result;
}
