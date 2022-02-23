#include <iostream>
#include <fstream>
#include "lib/Args.h"
#include "lib/RleCompressor.h"

int main(int argc, char* argv[])
{
	auto args = Args::ParseFromCLI(argc, argv);
	if (!args.has_value())
	{
		std::cerr
			<< "Invalid args. Usage: rle <action> <input file> <output file>" << std::endl
			<< "\t<action> must be 'pack' or 'unpack'";
		return 1;
	}

	std::ifstream inputFile(args->GetInputFilePath());
	if (!inputFile.good())
	{
		std::cerr << "Error while opening file " << args->GetInputFilePath() << std::endl;
	}

	std::ofstream outputFile(args->GetOutputFilePath());
	if (!outputFile.good())
	{
		std::cerr << "Error while opening file " << args->GetOutputFilePath() << std::endl;
	}

	bool res = args->GetAction() == ActionEnum::PACK ? RleCompressor::Compress(inputFile, outputFile) : RleCompressor::Decompress(inputFile, outputFile);
	if (!res)
	{
		std::cerr << "Error while performing " << (args->GetAction() == ActionEnum::PACK ? "compression" : "decompression") << std::endl;
		return 1;
	}

	std::cout << (args->GetAction() == ActionEnum::PACK ? "Compression" : "Decompression") << " complete" << std::endl;

	return 0;
}