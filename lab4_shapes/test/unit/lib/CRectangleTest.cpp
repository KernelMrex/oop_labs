#include "../../../../catch.hpp"
#include "../../../src/lib/CRectangle.h"
#include <cmath>

TEST_CASE("CRectangle unit tests", "[CRectangle_unit_tests]")
{
	SECTION("CRectangle must accept only valid width and height")
	{
		REQUIRE_NOTHROW(CRectangle(
			CPoint(5, 10),
			20,
			40,
			0x012345,
			0x098765));

		REQUIRE_THROWS_AS(CRectangle(
							  CPoint(5, 10),
							  -20,
							  40,
							  0x012345,
							  0x098765),
			std::invalid_argument);

		REQUIRE_THROWS_AS(CRectangle(
							  CPoint(5, 10),
							  20,
							  -40,
							  0x012345,
							  0x098765),
			std::invalid_argument);
	}

	SECTION("CRectangle must provide top_left point, bottom_right point, width and height")
	{
		CRectangle rectangle(
			CPoint(5, 10),
			20,
			40,
			0x012345,
			0x098765);

		REQUIRE(rectangle.GetLeftTop() == CPoint(5, 10));
		REQUIRE(rectangle.GetRightBottom() == CPoint(25, 50));
		REQUIRE(rectangle.GetWidth() == 20);
		REQUIRE(rectangle.GetHeight() == 40);
	}

	SECTION("CRectangle must calculate area")
	{
		CRectangle rectangle(
			CPoint(5, 10),
			20,
			40,
			0x012345,
			0x098765);
		REQUIRE(rectangle.GetArea() == 800);
	}

	SECTION("CRectangle must calculate perimeter")
	{
		CRectangle rectangle(
			CPoint(5, 10),
			20,
			40,
			0x012345,
			0x098765);

		REQUIRE(rectangle.GetPerimeter() == 120);
	}

	SECTION("CRectangle must provide outline and fill color")
	{
		CRectangle rectangle(
			CPoint(5, 10),
			20,
			40,
			0x012345,
			0x098765);
		REQUIRE(rectangle.GetOutlineColor() == 0x012345);
		REQUIRE(rectangle.GetFillColor() == 0x098765);
	}
}