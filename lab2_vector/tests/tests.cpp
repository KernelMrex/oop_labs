#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../vector_functions.h"

TEST_CASE("Reading simple numbers vector", "[simple]") {
    std::istringstream iss("9 1 8 3 7 4 5 2");
    std::ostringstream oss;

    ReadAndAddToEachItemSumOf3MinNumbers(iss, oss);
    REQUIRE( oss.str() == "7 8 9 10 11 13 14 15 \n" );
}

TEST_CASE("Reading error value vector", "[bad_vector]") {
    std::istringstream iss("9 1 8 3 7 4 5 2 qwerty 24");
    std::ostringstream oss;

    REQUIRE_THROWS(ReadAndAddToEachItemSumOf3MinNumbers(iss, oss));
}

TEST_CASE("Reading float numbers vector", "[float]") {
    std::istringstream iss("4.9 1.3 8 3.3 7 4 5 2");
    std::ostringstream oss;

    ReadAndAddToEachItemSumOf3MinNumbers(iss, oss);
    REQUIRE(oss.str() == "7.9 8.6 9.9 10.6 11.5 11.6 13.6 14.6 \n");
}
