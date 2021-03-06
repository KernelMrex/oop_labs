#include "FileDictionary.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

// Constructor
FileDictionary::FileDictionary(std::string path)
	: Dictionary()
	, path(std::move(path))
	, isSavedToFile(true)
{
}

// Destructor
FileDictionary::~FileDictionary() = default;

// Methods
void FileDictionary::AddTranslation(const std::string& phrase, const std::string& translation)
{
	this->isSavedToFile = false;
	Dictionary::AddTranslation(phrase, translation);
}

void FileDictionary::Load()
{
	std::ifstream file;
	file.open(this->path);
	if (!file.is_open())
	{
		std::ofstream dictFile(this->path);
		if (!dictFile.is_open())
		{
			throw std::runtime_error("could not open dictionary file");
		}
		dictFile.close();
		file.open(this->path);
		if (!file.is_open())
		{
			throw std::runtime_error("could not open dictionary file");
		}
	}
	LoadDictFromStream(file);
	file.close();
}

void FileDictionary::Save()
{
	std::ofstream file;
	file.open(this->path);
	if (!file.is_open())
	{
		throw std::runtime_error("could not open dictionary file");
	}
	SaveDictToStream(file);
	file.close();
	this->isSavedToFile = true;
}

void FileDictionary::SaveDictToStream(std::ostream& out)
{
	std::set<std::pair<std::string, std::string>> saved;

	auto dict = this->GetDict();
	for (auto wordIter = dict.begin(); wordIter != dict.end(); std::advance(wordIter, 1))
	{
		auto word = wordIter->first;
		auto transVars = wordIter->second;
		for (auto transVarIter = transVars.begin(); transVarIter != transVars.end(); std::advance(transVarIter, 1))
		{
			if (
				(saved.find(std::pair<std::string, std::string>(word, *transVarIter)) == saved.end()) && (saved.find(std::pair<std::string, std::string>(*transVarIter, word)) == saved.end()))
			{
				if (out.good())
				{
					out << word << "|" << *transVarIter << '\n';
					saved.insert(std::pair<std::string, std::string>(word, *transVarIter));
				}
				else
				{
					throw std::runtime_error("could not save dictionary");
				}
			}
		}
	}
}

void FileDictionary::LoadDictFromStream(std::istream& in)
{
	std::string line;
	while (in.good())
	{
		std::getline(in, line);
		std::stringstream ss(line);
		std::string word;
		std::string translation;
		getline(ss, word, '|');
		getline(ss, translation, '|');
		if (!word.empty() && !translation.empty())
		{
			Dictionary::AddTranslation(word, translation);
		}
	}
}

bool FileDictionary::isSaved()
{
	return this->isSavedToFile;
}
