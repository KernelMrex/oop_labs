#include "../../../../catch.hpp"
#include "../../../src/lib/CPoint.h"

TEST_CASE("CPoint unit tests", "[CPoint_unit_tests]")
{
	SECTION("CPoint must store x and y for point")
	{
		CPoint point(1, 2);
		REQUIRE(point.x == 1);
		REQUIRE(point.y == 2);
	}

	SECTION("CPoint must check equality")
	{
		CPoint point1(1, 2);
		CPoint point2(1, 2);
		REQUIRE(point1 == point2);
	}
}