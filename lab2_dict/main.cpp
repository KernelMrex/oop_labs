#include <iostream>
#include "Dictionary.h"

int main() {
    Dictionary dict;

    dict.AddTranslation("test", "тест");
    dict.AddTranslation("test", "испытания");
    dict.AddTranslation("cat", "собака");
    dict.AddTranslation("dog", "собака");
    dict.AddTranslation("mansion", "замок");
    dict.AddTranslation("lock", "замок");

    auto result = dict.Translate("test");
    if (!result.has_value()) {
        std::cout << "No such word" << std::endl;
        return 1;
    }

    auto transSet = result.value();
    for (auto it = transSet.begin(); it != transSet.end(); std::advance(it, 1)) {
        if (it != transSet.begin()) {
            std::cout << ", ";
        }
        std::cout << *it;
    }

    return 0;
}
