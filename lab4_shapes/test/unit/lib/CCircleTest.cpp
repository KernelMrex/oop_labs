#include "../../../../catch.hpp"
#include "../../../src/lib/CCircle.h"
#include <cmath>

TEST_CASE("CCircle unit tests", "[CCircle_unit_tests]")
{
	SECTION("CCircle must accept only valid width and height")
	{
		REQUIRE_NOTHROW(CCircle(
			CPoint(5, 10),
			20,
			0x012345,
			0x098765));

		REQUIRE_THROWS_AS(CCircle(
							  CPoint(5, 10),
							  -20,
							  0x012345,
							  0x098765),
			std::invalid_argument);
	}

	SECTION("CCircle must provide center and radius")
	{
		CCircle circle(
			CPoint(5, 10),
			20,
			0x012345,
			0x098765);

		REQUIRE(circle.GetCenter() == CPoint(5, 10));
		REQUIRE(circle.GetRadius() == 20);
	}

	SECTION("CCircle must calculate area")
	{
		CCircle circle(
			CPoint(5, 10),
			20,
			0x012345,
			0x098765);

		REQUIRE(circle.GetArea() == std::pow(20, 2) * M_PI);
	}

	SECTION("CCircle must calculate perimeter")
	{
		CCircle circle(
			CPoint(5, 10),
			20,
			0x012345,
			0x098765);

		REQUIRE(circle.GetPerimeter() == 2 * M_PI * 20);
	}

	SECTION("CCircle must provide outline and fill color")
	{
		CCircle circle(
			CPoint(5, 10),
			20,
			0x012345,
			0x098765);

		REQUIRE(circle.GetOutlineColor() == 0x012345);
		REQUIRE(circle.GetFillColor() == 0x098765);
	}

	SECTION("CCircle must provide dump")
	{
		CCircle circle1(
			CPoint(5, 10),
			20,
			0x012345,
			0x098765);

		REQUIRE(circle1.ToString() == "circle 5 10 20 0x012345 0x098765");

		CCircle circle(
			CPoint(5.1, 10.2),
			20.3,
			0x012345,
			0x098765);

		REQUIRE(circle.ToString() == "circle 5.1 10.2 20.3 0x012345 0x098765");
	}
}