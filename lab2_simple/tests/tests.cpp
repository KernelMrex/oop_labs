#define CATCH_CONFIG_MAIN

#include "../../catch.hpp"

#include "../prime_numbers.h"

TEST_CASE("up to 10 test", "[up_to_10]") {
    REQUIRE(GeneratePrimeNumbers(10) == std::set<int>{2, 3, 5, 7});
}

TEST_CASE("high upper bound tests", "[high_upper]") {
    auto begin = std::chrono::high_resolution_clock::now();
    auto primeNumbers = GeneratePrimeNumbers(100000000);
    auto end = std::chrono::high_resolution_clock::now();
    REQUIRE(primeNumbers.size());
    REQUIRE(std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() <= 12);
}

TEST_CASE("bad input", "[bad_input]") {
    REQUIRE(GeneratePrimeNumbers(1).empty());
    REQUIRE(GeneratePrimeNumbers(-1).empty());
    REQUIRE(GeneratePrimeNumbers(-1).empty());
    REQUIRE(GeneratePrimeNumbers(-1000).empty());
    REQUIRE(GeneratePrimeNumbers(3) == std::set<int>{2});
}
