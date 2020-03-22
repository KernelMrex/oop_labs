#include <iostream>
#include "FileDictionary.h"

std::optional<std::string> GetArgs(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    auto args = GetArgs(argc, argv);
    if (!args.has_value()) {
        std::cout << "Dictionary is not specified. Exiting..." << std::endl;
        std::cout << "Usage: dict <dictionary file>" << std::endl;
        return 1;
    }

    FileDictionary dict(args.value());
    dict.Load();
    std::cout << (dict.TranslateToString("lock").has_value() ? dict.TranslateToString("lock").value() : "")  << std::endl;

    return 0;
}

std::optional<std::string> GetArgs(int argc, char *argv[]) {
    if (argc != 2) {
        return std::nullopt;
    }
    return {argv[1]};
}
