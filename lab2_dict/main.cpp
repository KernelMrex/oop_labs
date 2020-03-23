#include "FileDictionary.h"
#include <iostream>

std::optional<std::string> GetArgs(int argc, char* argv[]);

void TranslateDialog(std::istream& in, std::ostream& out, FileDictionary& dict);

void SaveChangesDialog(std::istream& in, std::ostream& out, FileDictionary& dict);

int main(int argc, char* argv[])
{
	// Parsing args
	auto args = GetArgs(argc, argv);
	if (!args.has_value())
	{
		std::cout << "Dictionary is not specified. Exiting..." << std::endl;
		std::cout << "Usage: dict <dictionary file>" << std::endl;
		return 1;
	}

	// Init Dictionary
	FileDictionary dict(args.value());
	dict.Load();

	TranslateDialog(std::cin, std::cout, dict);

	SaveChangesDialog(std::cin, std::cout, dict);

	return 0;
}

std::optional<std::string> GetArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		return std::nullopt;
	}
	return { argv[1] };
}

void TranslateDialog(std::istream& in, std::ostream& out, FileDictionary& dict)
{
	while (in.good())
	{
		std::string wordToTranslate;
		out << "Enter a word to translate('...' to exit): ";
		std::getline(in, wordToTranslate);

		if (wordToTranslate == "...")
		{
			break;
		}

		auto translation = dict.TranslateToString(wordToTranslate);
		if (!translation.has_value())
		{
			out << "There is no such word in dictionary" << std::endl;
			out << "Enter a translation(empty string to skip): ";

			std::string newTranslation;
			std::getline(in, newTranslation);
			if (!newTranslation.empty())
			{
				dict.AddTranslation(wordToTranslate, newTranslation);
			}
		}
		else
		{
			out << translation.value() << std::endl;
		}
	}
}

void SaveChangesDialog(std::istream& in, std::ostream& out, FileDictionary& dict)
{
	if (!dict.isSaved())
	{
		while (in.good())
		{
			out << "Save new words(y\\n)?: ";
			std::string res;
			std::getline(in, res);
			if (res == "y")
			{
				out << "Saving dictionary and leaving..." << std::endl;
				dict.Save();
				return;
			}
			else if (res == "n")
			{
				out << "Leaving without saving..." << std::endl;
				return;
			}
			else
			{
				out << "No such option, repeat please" << std::endl;
			}
		}
	}
	out << "Leaving..." << std::endl;
}