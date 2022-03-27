#include <iostream>
#include <fstream>

#include "lib/Args.h"
#include "lib/CryptService.h"

void PerformCryptAction(const std::string& inputPath, const std::string& outputPath, Action action, unsigned char key);

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

	try
	{
		PerformCryptAction(args->GetInputFilePath(), args->GetOutputFilePath(), args->GetAction(), args->GetKey());
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void PerformCryptAction(const std::string& inputPath, const std::string& outputPath, Action action, unsigned char key)
{
	std::ifstream inputFile(inputPath);
	if (!inputFile.good())
	{
		throw std::runtime_error("Error while opening input file");
	}

	std::ofstream outputFile(outputPath);
	if (!outputFile.good())
	{
		throw std::runtime_error("Error while opening output file");
	}

	CryptService cryptService(key);

	if (!(action == Action::ENCRYPT ? cryptService.Encrypt(inputFile, outputFile) : cryptService.Decrypt(inputFile, outputFile)))
	{
		throw std::runtime_error("Error while performing encryption/decryption");
	}
}