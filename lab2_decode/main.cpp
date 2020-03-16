#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <memory>

struct Window {
	std::shared_ptr<char[]> content;
	int size;

	Window(int size) : size(size) {
		content = std::shared_ptr<char[]>(new char[size]);
		for (int i = 0; i < size; i++) {
			content[i] = 0;
		}
	}
};

typedef std::map<std::string, char> Dictionary;

std::string HtmlDecode(const std::string& html);

void HtmlDecode(std::istream& in, std::ostream& out, const Dictionary& chars);

std::optional<int> DetermineMaxKeyLength(const Dictionary& chars);

char MoveWindow(Window& window, char ch);

std::optional<char> GetReplace(Window& window, const Dictionary& dict);

bool isWordInWindow(const Window& window, const std::string& word);

int main() {
	try {
		std::cout << HtmlDecode("&lt;test&lt;ertqwertyuiop&gt;") << std::endl;
	} catch (const std::exception& err) {
		std::cout << "Error while decoding: " << err.what() << std::endl;
	}

	return 0;
}

std::string HtmlDecode(const std::string& html) {
	std::istringstream in(html);
	std::ostringstream out;

	std::map<std::string, char> chars = {
		{"&amp;",  '&'},
		{"&quot;", '\''},
		{"&lt;",   '<'},
		{"&gt;",   '>'}
	};

	HtmlDecode(in, out, chars);

	return out.str();
}

void HtmlDecode(std::istream& in, std::ostream& out, const Dictionary& chars) {
	// Determining minimal dynamic allocated window size
	auto windowSizeOptional = DetermineMaxKeyLength(chars);
	if (!windowSizeOptional.has_value()) {
		throw std::runtime_error("can not determine window size(dictionary may be empty)");
	}

	// Creating dynamic sized window
	Window window(windowSizeOptional.value());

	// Moving window
	char ch;
	while (in >> std::noskipws >> ch) {
		char popped = MoveWindow(window, ch);
		auto replaced = GetReplace(window, chars);
		if (popped != 0) {
			out << popped;
		}
		if (replaced.has_value()) {
			out << replaced.value();
		}
	}

	// Processing the rest of chars
	for (int i = 0; i < window.size; i++) {
		char popped = MoveWindow(window, ch);
		auto replaced = GetReplace(window, chars);
		if (popped != 0) {
			out << popped;
		}
		if (replaced.has_value()) {
			out << replaced.value();
		}
	}

	out << std::endl;
}

std::optional<int> DetermineMaxKeyLength(const Dictionary& chars) {
	if (chars.empty()) {
		return std::nullopt;
	}

	int max = 0;
	for (auto iterator = chars.begin(); iterator != chars.end(); std::advance(iterator, 1)) {
		if (iterator->first.length() > max) {
			max = iterator->first.length();
		}
	}

	return {max};
}

char MoveWindow(Window& window, char ch) {
	char poppedChar = window.content[0];
	for (int i = 0; i < window.size - 1; i++) {
		std::swap(window.content[i], window.content[i + 1]);
	}
	window.content[window.size - 1] = ch;
	return poppedChar;
}

std::optional<char> GetReplace(Window& window, const Dictionary& dict) {
	for (auto iter = dict.begin(); iter != dict.end(); std::advance(iter, 1)) {
		if (isWordInWindow(window, iter->first)) {
			for (int i = 0; i < iter->first.length(); i++) {
				window.content[i] = 0;
			}
			return {iter->second};
		}
	}
	return std::nullopt;
}

bool isWordInWindow(const Window& window, const std::string& word) {
	int i = 0;
	for (auto wordIter = word.begin(); wordIter != word.end(); std::advance(wordIter, 1), i++) {
		if (window.size <= i) {
			break;
		}
		if (*wordIter != window.content[i]) {
			return false;
		}
	}
	return true;
}