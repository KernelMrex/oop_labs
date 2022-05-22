#include "../../../../catch.hpp"
#include "../../../src/lib/shape_utils.h"
#include "../../../src/lib/CRectangle.h"

TEST_CASE("FindMaxArea unit tests", "[FindMaxArea_unit_tests]")
{
	SECTION("FindMaxArea must find shape with max area")
	{
		std::vector<std::unique_ptr<IShape>> shapes;

		shapes.push_back(std::make_unique<CRectangle>(CPoint(0, 1), 5, 10, 0xc0ffee, 0xc0ffee));
		shapes.push_back(std::make_unique<CRectangle>(CPoint(0, 1), 20, 30, 0xc0ffee, 0xc0ffee));
		shapes.push_back(std::make_unique<CRectangle>(CPoint(0, 1), 10, 15, 0xc0ffee, 0xc0ffee));

		REQUIRE(FindMaxArea(shapes) == (shapes.begin() + 1));
	}
}

TEST_CASE("FindMinPerimeter unit tests", "[FindMinPerimeter_unit_tests]")
{
	SECTION("FindMinPerimeter must find shape with min perimeter")
	{
		std::vector<std::unique_ptr<IShape>> shapes;

		shapes.push_back(std::make_unique<CRectangle>(CPoint(0, 1), 20, 30, 0xc0ffee, 0xc0ffee));
		shapes.push_back(std::make_unique<CRectangle>(CPoint(0, 1), 5, 10, 0xc0ffee, 0xc0ffee));
		shapes.push_back(std::make_unique<CRectangle>(CPoint(0, 1), 10, 15, 0xc0ffee, 0xc0ffee));

		REQUIRE(FindMinPerimeter(shapes) == (shapes.begin() + 1));
	}
}
