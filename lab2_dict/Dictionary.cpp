#include <set>
#include "Dictionary.h"

// Constructors
Dictionary::Dictionary() = default;

// Destructor
Dictionary::~Dictionary() = default;

// Methods
std::optional<std::set<std::string>> Dictionary::Translate(const std::string& phrase) {
    auto itemIterator = this->dict.find(phrase);
    if (itemIterator == dict.end()) {
        return std::nullopt;
    }
    return {itemIterator->second};
}

void Dictionary::AddTranslation(const std::string& phrase, const std::string& translation) {
    auto itemIterator = this->dict.find(phrase);
    if (itemIterator == dict.end()) {
        this->dict.insert(
                std::pair<std::string, std::set<std::string>>(phrase, {translation})
        );
        return;
    }

    auto setOfTranslations = &itemIterator->second;
    if (setOfTranslations->find(translation) == setOfTranslations->end()) {
        setOfTranslations->insert(translation);
    }
}
