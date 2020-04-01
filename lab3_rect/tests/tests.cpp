#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../CRectangle.h"

TEST_CASE("Getters and setters test", "[rect_getters_setters]")
{
	CRectangle rect{1, 6, 3, 4};
	REQUIRE(rect.GetLeft() == 1);
	REQUIRE(rect.GetRight() == 4);
	REQUIRE(rect.GetTop() == 6);
	REQUIRE(rect.GetBottom() == 2);

	// Updating all values using setters
	rect.SetAnchorX(11);
	rect.SetAnchorY(16);
	rect.SetWidth(13);
	rect.SetHeight(15);
	REQUIRE(rect.GetLeft() == 11);
	REQUIRE(rect.GetRight() == 24);
	REQUIRE(rect.GetTop() == 16);
	REQUIRE(rect.GetBottom() == 1);
}