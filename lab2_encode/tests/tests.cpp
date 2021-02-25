#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../encode.h"

TEST_CASE("Converting all symbols", "[all_separated]") {
    REQUIRE(HtmlEncode("& \" \' < >") == "&amp; &quot; &apos; &lt; &gt;");
}

TEST_CASE("Converting all symbols not separated", "[all_not_separated]") {
    REQUIRE(HtmlEncode("&\"\'<>") == "&amp;&quot;&apos;&lt;&gt;");
}

TEST_CASE("Convert on one symbol", "[no_one]") {
    REQUIRE(HtmlEncode("qwertyuiop asdfghjkl") == "qwertyuiop asdfghjkl");
}

TEST_CASE("Convert empty string", "[empty_string]") {
	REQUIRE(HtmlEncode("").empty());
}
