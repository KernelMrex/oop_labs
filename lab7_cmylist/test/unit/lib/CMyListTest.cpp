#include "../../../../catch.hpp"
#include "../../../src/lib/CMyList.h"

TEST_CASE("CMyList class unit tests")
{
	SECTION("CMyList must provide iterators that works like std::vector::iterator")
	{
		CMyList<int> list;
		list.Insert(list.begin(), 1);
		list.Insert(list.begin(), 2);
		list.Insert(++list.begin(), 3);
		list.Insert(list.begin(), 4);
		list.Insert(list.begin(), 5);
		list.Insert(list.end(), 99);
		list.Insert(list.begin(), 6);
		list.Insert(list.end(), 98);
		list.Delete(list.begin());
		list.Delete(--list.end());

		std::vector<int> v;
		v.insert(v.begin(), 1);
		v.insert(v.begin(), 2);
		v.insert(++v.begin(), 3);
		v.insert(v.begin(), 4);
		v.insert(v.begin(), 5);
		v.insert(v.end(), 99);
		v.insert(v.begin(), 6);
		v.insert(v.end(), 98);
		v.erase(v.begin());
		v.erase(--v.end());

		std::vector<int> listIterableValues;
		for (auto & it : list)
		{
			listIterableValues.push_back(it.GetValue());
		}

		REQUIRE(listIterableValues == v);
	}

	SECTION("CMyList must provide reverse iterator")
	{
		CMyList<int> list;
		list.Insert(list.end(), 1);
		list.Insert(list.end(), 2);
		list.Insert(list.end(), 3);
		list.Insert(list.end(), 4);
		list.Insert(list.end(), 5);

		std::vector<int> listIterableValues;
		for (auto it = list.rbegin(); it != list.rend(); it++)
		{
			listIterableValues.push_back(it->GetValue());
		}

		REQUIRE(listIterableValues == std::vector<int>{5, 4, 3, 2, 1});
	}

	SECTION("CMyList must provide PushFront/PushBack interface")
	{
		WHEN("Using PushFront")
		{
			CMyList<int> list;
			list.PushFront(1);
			list.PushFront(2);
			list.PushFront(3);

			std::vector<int> listIterableValues;
			for (auto it = list.begin(); it != list.end(); it++)
			{
				listIterableValues.push_back(it->GetValue());
			}

			REQUIRE(listIterableValues == std::vector<int>{3, 2, 1});
		}

		WHEN("Using PushBack")
		{
			CMyList<int> list;
			list.PushBack(1);
			list.PushBack(2);
			list.PushBack(3);

			std::vector<int> listIterableValues;
			for (auto it = list.begin(); it != list.end(); it++)
			{
				listIterableValues.push_back(it->GetValue());
			}

			REQUIRE(listIterableValues == std::vector<int>{1, 2, 3});
		}
	}

	SECTION("CMyList must provide GetSize interface")
	{
		CMyList<int> list;

		REQUIRE(list.GetSize() == 0);

		list.PushBack(1);
		list.PushBack(2);
		list.PushBack(3);

		REQUIRE(list.GetSize() == 3);

		list.Delete(list.begin());
		list.Delete(list.begin());

		REQUIRE(list.GetSize() == 1);
	}

	SECTION("CMyList must provide IsEmpty interface")
	{
		CMyList<int> list;
		REQUIRE(list.IsEmpty());
		list.PushBack(1);
		REQUIRE_FALSE(list.IsEmpty());
	}
}