#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../CRectangle.h"

TEST_CASE("Getters and setters test", "[rect_getters_setters]")
{
	CRectangle rect{ 1, 2, 3, 4 };
	REQUIRE(rect.GetLeft() == 1);
	REQUIRE(rect.GetRight() == 3);
	REQUIRE(rect.GetTop() == 2);
	REQUIRE(rect.GetBottom() == 5);

	// Updating all values using setters
	rect.SetNewAnchorPos(11, 12);
	rect.SetWidth(13);
	rect.SetHeight(14);
	REQUIRE(rect.GetLeft() == 11);
	REQUIRE(rect.GetRight() == 23);
	REQUIRE(rect.GetTop() == 12);
	REQUIRE(rect.GetBottom() == 25);
}

TEST_CASE("Incorrect setters values", "[bad_setters_values]")
{
	CRectangle rect{ -1, -1, -1, -1 };
	REQUIRE(rect.GetLeft() == 0);
	REQUIRE(rect.GetRight() == 0);
	REQUIRE(rect.GetTop() == 0);
	REQUIRE(rect.GetBottom() == 0);

	rect.SetWidth(-1);
	rect.SetHeight(-1);
	rect.SetNewAnchorPos(-1, -1);
	REQUIRE(rect.GetLeft() == 0);
	REQUIRE(rect.GetRight() == 0);
	REQUIRE(rect.GetTop() == 0);
	REQUIRE(rect.GetBottom() == 0);
}

TEST_CASE("Intersect check", "[intersect_check]")
{
	/**    1 2 3 4 5 6
	 *   #------------
	 * 1 | 0 0 0 0 0 0
	 * 2 | 0 2 2 2 0 0
	 * 3 | 0 2 2 2 0 0
	 * 4 |   1 1 1
	 * 5 |   1 1 1
	 */
	CRectangle rect1{ 1, 1, 6, 3 };
	CRectangle rect2{ 2, 2, 3, 4 };
	REQUIRE(rect1.Intersect(rect2));

	/**    1 2 3 4 5 6
	 *   #------------
	 * 1 |     0 0
	 * 2 |     0 0
	 * 3 | 1 1 2 2 1 1
	 * 4 |     0 0
	 * 5 |
	 */
	CRectangle rect3{ 3, 1, 2, 4 };
	CRectangle rect4{ 1, 3, 6, 1 };
	REQUIRE(rect3.Intersect(rect4));

	/**    1 2 3 4 5 6
	 *   #------------
 	 * 1 |
 	 * 2 |   0 0 0 0
 	 * 3 |   0 2 2 0
 	 * 4 |   0 2 2 0
     * 5 |   0 0 0 0
 	 */
	CRectangle rect5{ 2, 2, 4, 4 };
	CRectangle rect6{ 3, 3, 2, 2 };
	REQUIRE(rect5.Intersect(rect6));

	/**    1 2 3 4 5 6
 	 *   #------------
  	 * 1 | 0 0
	 * 2 | 0 0 1 1 1
     * 3 | 0 0 1 1 1
     * 4 |     1 1 1
     * 5 |
	 */
	CRectangle rect7{ 1, 1, 2, 3 };
	CRectangle rect8{ 3, 2, 3, 3 };
	REQUIRE_FALSE(rect7.Intersect(rect8));
}

TEST_CASE("Move test", "[movement]")
{
	/** Move test
     *     1 2 3 4 5 6            1 2 3 4 5 6
     *   #------------          #------------
     * 1 | 0 0                1 |
     * 2 | 0 0                2 |
     * 3 | 0 0            ==> 3 |   0 0
     * 4 |                    4 |   0 0
     * 5 |                    5 |   0 0
     */
	CRectangle rect{ 1, 1, 2, 3 };
	rect.Move(1, 2);
	REQUIRE(rect.GetLeft() == 2);
	REQUIRE(rect.GetRight() == 3);
	REQUIRE(rect.GetTop() == 3);
	REQUIRE(rect.GetBottom() == 5);

	/**  Negative value movement
     *     0 1 2 3 4 5            0 1 2 3 4 5
     *   #------------          #------------
     * 0 |                    0 | 0 0
     * 1 |                    1 | 0 0
     * 2 |                ==> 2 | 0 0
     * 3 |   0 0              3 |
     * 4 |   0 0              4 |
     * 5 |   0 0              5 |
     */
	rect.Move(-2, -3);
	REQUIRE(rect.GetLeft() == 0);
	REQUIRE(rect.GetRight() == 1);
	REQUIRE(rect.GetTop() == 0);
	REQUIRE(rect.GetBottom() == 2);

	/** Negative result test
     * No movement because movement resulting negative values
     */
	rect.Move(-5, -5);
	REQUIRE(rect.GetLeft() == 0);
	REQUIRE(rect.GetRight() == 1);
	REQUIRE(rect.GetTop() == 0);
	REQUIRE(rect.GetBottom() == 2);
}

TEST_CASE("Scale test", "[scale]")
{
	/** Scale test
     *     1 2 3 4 5 6            1 2 3 4 5 6
     *   #------------          #------------
     * 1 | 0 0                1 | 0 0 0 0
     * 2 | 0 0                2 | 0 0 0 0
     * 3 |                ==> 3 | 0 0 0 0
     * 4 |                    4 |
     * 5 |                    5 |
     */
	CRectangle rect{ 1, 1, 2, 2 };
	rect.Scale(2, 1);
	REQUIRE(rect.GetLeft() == 1);
	REQUIRE(rect.GetRight() == 4);
	REQUIRE(rect.GetTop() == 1);
	REQUIRE(rect.GetBottom() == 3);

	/** Scale test
     *     1 2 3 4 5 6            1 2 3 4 5 6
     *   #------------          #------------
     * 1 | 0 0 0 0            1 | 0 0 0
     * 2 | 0 0 0 0            2 |
     * 3 | 0 0 0 0        ==> 3 |
     * 4 |                    4 |
     * 5 |                    5 |
     */
	rect.Scale(-1, -2);
	REQUIRE(rect.GetLeft() == 1);
	REQUIRE(rect.GetRight() == 3);
	REQUIRE(rect.GetTop() == 1);
	REQUIRE(rect.GetBottom() == 1);
}