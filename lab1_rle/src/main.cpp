#include <iostream>
#include <fstream>
#include "lib/Args.h"
#include "lib/RleCompressor.h"

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

	std::ifstream inputFile(args->getInputFilePath());
	if (!inputFile.good())
	{
		std::cerr << "Error while opening file " << args->getInputFilePath() << std::endl;
	}

	std::ofstream outputFile(args->getOutputFilePath());
	if (!outputFile.good())
	{
		std::cerr << "Error while opening file " << args->getOutputFilePath() << std::endl;
	}

	RleCompressor compressor(inputFile, outputFile);

	bool res = args->getAction() == ActionEnum::PACK ? compressor.compress() : compressor.decompress();
	if (!res)
	{
		std::cerr << "Error while performing " << (args->getAction() == ActionEnum::PACK ? "compression" : "decompression") << std::endl;
		return 1;
	}

	std::cout << (args->getAction() == ActionEnum::PACK ? "Compression" : "Decompression") << " complete" << std::endl;

	return 0;
}