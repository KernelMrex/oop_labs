#include "../../../../catch.hpp"
#include "../../../src/lib/find_max_ex.h"

TEST_CASE("FindMaxEx function tests")
{
	SECTION("FindMaxEx must put max element in 2nd arg")
	{
		WHEN("arr is (0, 1, 2, 3, 4, 5)")
		{
			std::vector<int> arr{0, 1, 2, 3, 4, 5};
			int maxValue = -1;

			auto res = FindMaxEx(arr, maxValue, [](int a, int b) -> bool {
				return a < b;
			});
			REQUIRE(res == true);
			REQUIRE(maxValue == 5);
		}


		WHEN("arr is (0, 1, 3, 1, 2, 2)")
		{
			std::vector<int> arr{0, 1, 3, 1, 2, 2};
			int maxValue = -1;

			auto res = FindMaxEx(arr, maxValue, [](int a, int b) -> bool {
				return a < b;
			});
			REQUIRE(res == true);
			REQUIRE(maxValue == 3);
		}

		WHEN("arr is (5, 1, 3, 1, 2, 2)")
		{
			std::vector<int> arr{5, 1, 3, 1, 2, 2};
			int maxValue = -1;

			auto res = FindMaxEx(arr, maxValue, [](int a, int b) -> bool {
				return a < b;
			});
			REQUIRE(res == true);
			REQUIRE(maxValue == 5);
		}

		WHEN("arr is (5, -1337, 3, 8, -2, 2)")
		{
			std::vector<int> arr{5, -1337, 3, 8, -2, 2};
			int maxValue = -1;

			auto res = FindMaxEx(arr, maxValue, [](int a, int b) -> bool {
				return a < b;
			});
			REQUIRE(res == true);
			REQUIRE(maxValue == 8);
		}
	}

	SECTION("FindMaxEx must follow the principle commit-or-rollback")
	{
		std::vector<int> arr{};
		int maxValue = 777;

		auto res = FindMaxEx(arr, maxValue, [](int a, int b) -> bool {
			return a < b;
		});

		REQUIRE(res == false);
		REQUIRE(maxValue == 777);
	}

}