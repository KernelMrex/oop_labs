#include "CRectangle.h"
#include <iostream>
#include <optional>

struct Args
{
	std::string InputFile;
	std::string OutputFile;
};

std::optional<Args> GetArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	auto args = GetArgs(argc, argv);
	if (!args.has_value())
	{
		std::cout << "Bad arguments. Usage: rect <input file> <output file>";
		return 1;
	}

	std::cout << "In: " << args->InputFile << std::endl
			  << " Out: " << args->OutputFile << std::endl;

	return 0;
}

std::optional<Args> GetArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		return std::nullopt;
	}
	return (std::optional<Args>){
		(Args){
			argv[1],
			argv[2] }
	};
}
