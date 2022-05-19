#include "../../../../catch.hpp"
#include "../../../src/lib/CLineSegment.h"
#include <cmath>

TEST_CASE("CLineSegment unit tests", "[CLineSegment_unit_tests]")
{
	SECTION("CLineSegment must calculate perimeter")
	{
		CLineSegment lineSegment1(CPoint(1, 2), CPoint(3, 4), 0);
		REQUIRE(lineSegment1.GetPerimeter() == sqrt(8));

		CLineSegment lineSegment2(CPoint(0, 0), CPoint(3, 4), 0);
		REQUIRE(lineSegment2.GetPerimeter() == 5);
	}

	SECTION("CLineSegment must calculate area equals to 0")
	{
		CLineSegment lineSegment(CPoint(1, 2), CPoint(3, 4), 0);
		REQUIRE(lineSegment.GetArea() == 0);
	}

	SECTION("CLineSegment must provide starting and ending points")
	{
		CPoint startPosition(1, 2);
		CPoint endPosition(3, 4);
		CLineSegment lineSegment(startPosition, endPosition, 0);
		REQUIRE(lineSegment.GetStartPoint() == startPosition);
		REQUIRE(lineSegment.GetEndPoint() == endPosition);
	}

	SECTION("CLineSegment must provide outline color")
	{
		uint32_t outlineColor = 0x123456;
		CLineSegment lineSegment(CPoint(1, 2), CPoint(3, 4), outlineColor);
		REQUIRE(lineSegment.GetOutlineColor() == outlineColor);

	}

	SECTION("CLineSegment must provide dump")
	{
	}
}