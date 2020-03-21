#include <iostream>
#include "Dictionary.h"

int main() {
    Dictionary dict;

    dict.AddTranslation("test", "тест");
    dict.AddTranslation("test", "испытания");
    dict.AddTranslation("cat", "кошка");
    dict.AddTranslation("dog", "собака");
    dict.AddTranslation("mansion", "замок");
    dict.AddTranslation("lock", "замок");

    auto res = dict.TranslateToString("test");
    if (!res.has_value()) {
        std::cout << "No such word in dictionary" << std::endl;
        return 1;
    }
    std::cout << res.value() << std::endl;

    return 0;
}
