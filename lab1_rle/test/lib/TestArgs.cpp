#include "../../../catch.hpp"
#include "../../src/lib/Args.h"

TEST_CASE("Args class must parse arguments from cli", "[args]")
{
	SECTION("Successful parsing")
	{
		char *argv[] = {"rle", "pack", "in.txt", "out.txt"};
		int argc = 4;
		auto args = Args::parseFromCLI(argc, argv);

		REQUIRE(args.has_value());
		REQUIRE(args->getAction() == ActionEnum::PACK);
		REQUIRE(args->getInputFilePath() == "in.txt");
		REQUIRE(args->getOutputFilePath() == "out.txt");
	}

	SECTION("Invalid amount of arguments")
	{
		char *argv[] = {"rle", "pack"};
		int argc = 2;
		auto args = Args::parseFromCLI(argc, argv);

		REQUIRE_FALSE(args.has_value());
	}

	SECTION("Incorrect action")
	{
		char *argv[] = {"rle", "incorrect_action", "in.txt", "out.txt"};
		int argc = 4;
		auto args = Args::parseFromCLI(argc, argv);

		REQUIRE_FALSE(args.has_value());
	}
}