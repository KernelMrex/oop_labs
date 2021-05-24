#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../src/Complex/Complex.h"

TEST_CASE("complex numbers can be constructed", "[complex_class]")
{
	SECTION("constructing and getting mixed values")
	{
		Complex complex(12, -23);
		REQUIRE(complex.Re() == 12.0);
		REQUIRE(complex.Im() == -23.0);

		REQUIRE(complex.GetArgument() == 23.0);
		REQUIRE(complex.GetMagnitude() == 12.0);
	}

	SECTION("constructing and getting positive values")
	{
		Complex complex(12, 23);
		REQUIRE(complex.Re() == 12.0);
		REQUIRE(complex.Im() == 23.0);
		REQUIRE(complex.GetArgument() == 23.0);
		REQUIRE(complex.GetMagnitude() == 12.0);
	}

	SECTION("constructing and getting negative values")
	{
		Complex complex(-12, -23);
		REQUIRE(complex.Re() == -12.0);
		REQUIRE(complex.Im() == -23.0);
		REQUIRE(complex.GetArgument() == 23.0);
		REQUIRE(complex.GetMagnitude() == 12.0);
	}
}