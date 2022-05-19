#include "../../../../catch.hpp"
#include "../../../src/lib/CTriangle.h"
#include <cmath>

TEST_CASE("CTriangle unit tests", "[CTriangle_unit_tests]")
{
	SECTION("CTriangle must provide vertices")
	{
		CTriangle triangle(
			CPoint(0, 0),
			CPoint(0, 1),
			CPoint(1, 1),
			0x012345,
			0x098765
		);

		REQUIRE(triangle.GetVertex1() == CPoint(0, 0));
		REQUIRE(triangle.GetVertex2() == CPoint(0, 1));
		REQUIRE(triangle.GetVertex3() == CPoint(1, 1));
	}

	SECTION("CTriangle must calculate area")
	{
		CTriangle triangle(
			CPoint(0, 0),
			CPoint(0, 3),
			CPoint(4, 3),
			0x012345,
			0x098765
		);
		REQUIRE(triangle.GetArea() == 6);

		CTriangle triangle2(
			CPoint(0, 0),
			CPoint(0, 5),
			CPoint(12, 5),
			0x012345,
			0x098765
		);
		REQUIRE(triangle2.GetArea() == 30);
	}

	SECTION("CTriangle must calculate perimeter")
	{
		CTriangle triangle1(
			CPoint(0, 0),
			CPoint(0, 5),
			CPoint(12, 5),
			0x012345,
			0x098765
		);
		REQUIRE(triangle1.GetPerimeter() == 30);

		CTriangle triangle2(
			CPoint(0, 0),
			CPoint(0, 3),
			CPoint(4, 3),
			0x012345,
			0x098765
		);
		REQUIRE(triangle2.GetPerimeter() == 12);
	}

	SECTION("CTriangle must provide outline and fill color")
	{
		CTriangle triangle(
			CPoint(0, 0),
			CPoint(0, 5),
			CPoint(12, 5),
			0x012345,
			0x098765
		);
		REQUIRE(triangle.GetOutlineColor() == 0x012345);
		REQUIRE(triangle.GetFillColor() == 0x098765);
	}

	SECTION("CTriangle must provide dump")
	{

	}
}