#include <iostream>
#include "lib/Args.h"

int main(int argc, char* argv[])
{
	auto args = Args::parseFromCLI(argc, argv);
	if (!args.has_value())
	{
		std::cerr
			<< "Invalid args. Usage: rle <action> <input file> <output file>" << std::endl
			<< "\t<action> must be 'pack' or 'unpack'";
		return 1;
	}

	return 0;
}