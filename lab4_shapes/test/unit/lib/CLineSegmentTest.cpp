#include "../../../../catch.hpp"
#include "../../../src/lib/CLineSegment.h"
#include <cmath>

TEST_CASE("CLineSegment unit tests", "[CLineSegment_unit_tests]")
{
	SECTION("CLineSegment must calculate perimeter")
	{
		CLineSegment lineSegment(CPoint(1, 2), CPoint(3, 4), 0);
		REQUIRE(lineSegment.GetPerimeter() == sqrt(8));
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
		CLineSegment lineSegment(CPoint(1, 2), CPoint(3, 4), 0x012345);
		REQUIRE(lineSegment.ToString() == "line_segment 1 2 3 4 0x012345");
	}
}