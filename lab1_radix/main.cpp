#include <cmath>
#include <iostream>
#include <optional>
#include <string>

#define MAX_RADIX 36
#define MIN_RADIX 2

/* Headers */
bool IsCapitalLetter(char ch);

bool IsDigit(char ch);

uint8_t CharToIntRadix(char ch, uint8_t radix);

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
		std::cout << decimalNumberView << std::endl;

		// TODO: std::cout << IntToString(decimalNumberView, result->destinationNotation) << std::endl;
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

	long result = 0;
	int offset = 0;
	for (int i = (int) str.length() - 1; i >= 0; i--) {
		result = result + ((long) pow(radix, offset)) * CharToIntRadix(str[i], radix);
		offset++;
	}

	return result;
}

// TODO
std::string IntToString(long n, uint8_t radix) {
	return "";
}
