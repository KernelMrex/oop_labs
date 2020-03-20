#include <iostream>
#include <map>
#include <vector>

#include "decode.h"

int main() {
	try {
		std::string line;
		while (std::cin.good()) {
			std::getline(std::cin, line);
			std::cout << HtmlDecode(line) << std::endl;
		}
	} catch (const std::exception& err) {
		std::cout << "Error while decoding: " << err.what() << std::endl;
	}

	return 0;
}
