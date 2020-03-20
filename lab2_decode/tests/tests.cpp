#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../decode.h"

TEST_CASE("Converting all symbols", "[all_separated]") {
    REQUIRE(HtmlDecode("&amp; &quot; &apos; &lt; &gt;") == "& \" \' < >");
}

TEST_CASE("Converting all symbols not separated", "[all_not_separated]") {
    REQUIRE(HtmlDecode("&amp;&quot;&apos;&lt;&gt;") == "&\"\'<>");
}

TEST_CASE("Convert on one symbol", "[no_one]") {
    REQUIRE(HtmlDecode("qwertyuiop asdfghjkl") == "qwertyuiop asdfghjkl");
}
