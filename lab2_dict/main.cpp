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

    dict.AddTranslation("cat", "кошка");
    dict.AddTranslation("dog", "собака");
    dict.AddTranslation("test", "тест");
    dict.AddTranslation("test", "испытание");
    dict.AddTranslation("mansion", "замок");
    dict.AddTranslation("lock", "замок");
    dict.Save();

    return 0;
}

std::optional<std::string> GetArgs(int argc, char *argv[]) {
    if (argc != 2) {
        return std::nullopt;
    }
    return {argv[1]};
}
