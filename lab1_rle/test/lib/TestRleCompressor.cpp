#include <sstream>
#include "../../../catch.hpp"
#include "../../src/lib/RleCompressor.h"

TEST_CASE("RleCompressor class must compress or decompress", "[rle_compressor]")
{
	SECTION("Compressing simple string")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << "AAAAABBBC";
		RleCompressor compressor(iss, oss);
		compressor.compress();

		std::stringstream res;
		res << (char) 5 << "A" << (char) 3 << "B" << (char) 1 << "C";

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Compress string with every unique char")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << "ABCD";
		RleCompressor compressor(iss, oss);
		compressor.compress();

		std::stringstream res;
		res << (char) 1 << "A" << (char) 1 << "B" << (char) 1 << "C" << (char) 1 << "D";

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Compress string with repeat char sequence more than 255 chars")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << std::string(256, 'A') + "CD";
		RleCompressor compressor(iss, oss);
		compressor.compress();

		std::stringstream res;
		res << (char) 255 << "A" << (char) 1 << "A" << (char) 1 << "C" << (char) 1 << "D";

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Compress string with repeat char sequence more than 255 chars at the middle of the string")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << "AB" + std::string(258, 'C') + "D";
		RleCompressor compressor(iss, oss);
		compressor.compress();

		std::stringstream res;
		res << (char) 1 << "A" << (char) 1 << "B" << (char) 255 << "C" << (char) 3 << "C" << (char) 1 << "D";

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Compress string with repeat char sequence more than 255 chars at ending of the string")
	{
		std::stringstream iss;
		std::stringstream oss;

		iss << "AB" + std::string(258, 'C');
		RleCompressor compressor(iss, oss);
		compressor.compress();

		std::stringstream res;
		res << (char) 1 << "A" << (char) 1 << "B" << (char) 255 << "C" << (char) 3 << "C";

		REQUIRE(oss.str() == res.str());
	}
}
