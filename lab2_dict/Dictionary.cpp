#include "Dictionary.h"
#include "string_utils.h"
#include <set>
#include <sstream>

// Constructors
Dictionary::Dictionary() = default;

// Destructor
Dictionary::~Dictionary() = default;

// Methods
std::optional<std::set<std::string>> Dictionary::Translate(const std::string& phrase)
{
	auto itemIterator = this->dict.find(StringToLowerUTF8(phrase));
	if (itemIterator == dict.end())
	{
		return std::nullopt;
	}
	return { itemIterator->second };
}

std::optional<std::string> Dictionary::TranslateToString(const std::string& phrase)
{
	auto translations = this->Translate(phrase);
	if (!translations.has_value())
	{
		return std::nullopt;
	}

	std::ostringstream result;
	auto transSet = translations.value();
	for (auto it = transSet.begin(); it != transSet.end(); std::advance(it, 1))
	{
		if (it != transSet.begin())
		{
			result << ", ";
		}
		result << *it;
	}

	return { result.str() };
}

void Dictionary::AddTranslation(const std::string& phrase, const std::string& translation)
{
	auto FormattedPhrase = StringToLowerUTF8(phrase);
	auto FormattedTranslation = StringToLowerUTF8(translation);
	this->AddOneWayTranslation(FormattedPhrase, FormattedTranslation);
	this->AddOneWayTranslation(FormattedTranslation, FormattedPhrase);
}

void Dictionary::AddOneWayTranslation(const std::string& phrase, const std::string& translation)
{
	auto itemIterator = this->dict.find(phrase);
	if (itemIterator == dict.end())
	{
		this->dict.insert(
			std::pair<std::string, std::set<std::string>>(phrase, { translation }));
		return;
	}

	auto setOfTranslations = &itemIterator->second;
	if (setOfTranslations->find(translation) == setOfTranslations->end())
	{
		setOfTranslations->insert(translation);
	}
}

const std::map<std::string, std::set<std::string>>& Dictionary::GetDict()
{
	return this->dict;
}
