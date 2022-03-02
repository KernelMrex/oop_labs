#include <iostream>
#include <fstream>

#include "lib/Args.h"
#include "lib/CryptService.h"

int main(int argc, char* argv[])
{
	auto args = Args::ParseFromCLI(argc, argv);
	if (!args.has_value())
	{
		std::cerr
			<< "Invalid args. Usage: crypt <action> <input file> <output file> <key>" << std::endl
			<< "\t<action> must be 'encrypt' or 'decrypt'" << std::endl
			<< "\t<key> must be number in range 0-255" << std::endl;
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

	bool res = args->GetAction() == ActionEnum::ENCRYPT
		? CryptService::Encrypt(inputFile, outputFile, args->getKey())
		: CryptService::Decrypt(inputFile, outputFile, args->getKey());
	if (!res)
	{
		std::cerr << "Error while performing " << (args->GetAction() == ActionEnum::ENCRYPT ? "encryption" : "decryption") << std::endl;
		return 2;
	}

	std::cout << (args->GetAction() == ActionEnum::ENCRYPT ? "Encryption" : "Decryption") << " complete" << std::endl;

	return 0;
}