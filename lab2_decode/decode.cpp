#include <sstream>
#include "decode.h"

std::string HtmlDecode(const std::string& html) {
    std::istringstream in(html);
    std::ostringstream out;

    std::map<std::string, char> chars = {
            {"&amp;",  '&'},
            {"&quot;", '\"'},
            {"&apos;", '\''},
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
        PushNextToDecoder(window, ch, chars, out);
    }

    if (!in.eof() && in.fail()) {
        throw std::runtime_error("error while reading input stream");
    }

    // Processing the rest of chars
    for (int i = 0; i < window.size; i++) {
        PushNextToDecoder(window, ch, chars, out);
    }
}

void PushNextToDecoder(Window& window, char ch, const Dictionary& dict, std::ostream& out) {
    auto popped = MoveWindow(window, ch);
    auto replaced = GetReplace(window, dict);
    if (popped.has_value()) {
        out << popped.value();
    }
    if (replaced.has_value()) {
        out << replaced.value();
    }
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

std::optional<char> MoveWindow(Window& window, char ch) {
    char poppedChar = window.content[0];
    for (int i = 0; i < window.size - 1; i++) {
        std::swap(window.content[i], window.content[i + 1]);
    }
    window.content[window.size - 1] = ch;

    if (poppedChar == 0) {
        return std::nullopt;
    }
    return {poppedChar};
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