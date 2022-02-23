#include <sstream>
#include "../../../catch.hpp"
#include "../../src/lib/RleCompressor.h"

TEST_CASE("RleCompressor class must Compress or Decompress", "[rle_compressor]")
{
	SECTION("Compressing simple string")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << "AAAAABBBC";
		RleCompressor::Compress(iss, oss);

		std::stringstream res;
		res << (char) 5 << "A" << (char) 3 << "B" << (char) 1 << "C";

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Compress string with every unique char")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << "ABCD";
		RleCompressor::Compress(iss, oss);

		std::stringstream res;
		res << (char) 1 << "A" << (char) 1 << "B" << (char) 1 << "C" << (char) 1 << "D";

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Compress string with repeat char sequence more than 255 chars")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << std::string(256, 'A') + "CD";
		RleCompressor::Compress(iss, oss);

		std::stringstream res;
		res << (char) 255 << "A" << (char) 1 << "A" << (char) 1 << "C" << (char) 1 << "D";

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Compress string with repeat char sequence more than 255 chars at the middle of the string")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << "AB" + std::string(258, 'C') + "D";
		RleCompressor::Compress(iss, oss);

		std::stringstream res;
		res << (char) 1 << "A" << (char) 1 << "B" << (char) 255 << "C" << (char) 3 << "C" << (char) 1 << "D";

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Compress string with repeat char sequence more than 255 chars at ending of the string")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << "AB" + std::string(258, 'C');
		RleCompressor::Compress(iss, oss);

		std::stringstream res;
		res << (char) 1 << "A" << (char) 1 << "B" << (char) 255 << "C" << (char) 3 << "C";

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Decompressing simple string")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << (char) 5 << "A" << (char) 3 << "B" << (char) 1 << "C";
		RleCompressor::Decompress(iss, oss);

		std::stringstream res;
		res << "AAAAABBBC";

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Decompress string with every unique char")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << (char) 1 << "A" << (char) 1 << "B" << (char) 1 << "C" << (char) 1 << "D";
		RleCompressor::Decompress(iss, oss);

		std::stringstream res;
		res << "ABCD";

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Decompress string with repeat char sequence more than 255 chars")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << (char) 255 << "A" << (char) 1 << "A" << (char) 1 << "C" << (char) 1 << "D";
		RleCompressor::Decompress(iss, oss);

		std::stringstream res;
		res << std::string(256, 'A') + "CD";

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Decompress string with repeat char sequence more than 255 chars at the middle of the string")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << (char) 1 << "A" << (char) 1 << "B" << (char) 255 << "C" << (char) 3 << "C" << (char) 1 << "D";
		RleCompressor::Decompress(iss, oss);

		std::stringstream res;
		res << "AB" + std::string(258, 'C') + "D";

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Decompress string with repeat char sequence more than 255 chars at ending of the string")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << (char) 1 << "A" << (char) 1 << "B" << (char) 255 << "C" << (char) 3 << "C";
		RleCompressor::Decompress(iss, oss);

		std::stringstream res;
		res << "AB" + std::string(258, 'C');

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Decompress invalid string")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << "ABC";
		bool res = RleCompressor::Decompress(iss, oss);

		REQUIRE_FALSE(res);
	}
}
