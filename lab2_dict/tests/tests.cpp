#define CATCH_CONFIG_MAIN

#include "../../catch.hpp"
#include "../Dictionary.h"

TEST_CASE("Simple translation", "[simple]") {
    Dictionary dict;
    dict.AddTranslation("cat", "кошка");
    dict.AddTranslation("dog", "собака");
    REQUIRE(dict.TranslateToString("dog").value() == "собака");
}

TEST_CASE("Multi words translation", "[multiwords]") {
    Dictionary dict;
    dict.AddTranslation("cat", "кошка");
    dict.AddTranslation("dog", "собака");
    dict.AddTranslation("test", "тест");
    dict.AddTranslation("test", "испытание");
    dict.AddTranslation("mansion", "замок");
    dict.AddTranslation("lock", "замок");
    REQUIRE(dict.TranslateToString("замок").value() == "lock, mansion");
    REQUIRE(dict.TranslateToString("test").value() == "испытание, тест");
}

TEST_CASE("No such word", "[no_such_word]") {
    Dictionary dict;
    dict.AddTranslation("cat", "кошка");
    dict.AddTranslation("dog", "собака");
    REQUIRE(!dict.TranslateToString("bee").has_value());
}

TEST_CASE("Empty dictionary", "[empty_dict]") {
    Dictionary dict;
    REQUIRE(!dict.TranslateToString("something").has_value());
}
