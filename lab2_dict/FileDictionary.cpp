#include "FileDictionary.h"

#include <utility>
#include <iostream>
#include <fstream>

// Constructor
FileDictionary::FileDictionary(std::string path) : path(std::move(path)) {}

// Destructor
FileDictionary::~FileDictionary() = default;

// Methods
void FileDictionary::Load() {}

void FileDictionary::Save() {
    std::ofstream file;
    file.open(this->path);
    if (!file.is_open()) {
        throw std::runtime_error("could not open dictionary file");
    }

    SaveDictToStream(file);

    file.close();
}

void FileDictionary::SaveDictToStream(std::ostream& out) {
    auto dict = this->GetDict();
    for (auto wordIter = dict.begin(); wordIter != dict.end(); std::advance(wordIter, 1)) {
        out << wordIter->first;
        auto transVars = wordIter->second;
        for (auto transVarIter = transVars.begin(); transVarIter != transVars.end(); std::advance(transVarIter, 1)) {
            out << "|" << *transVarIter;
        }
        out << '\n';
    }
}
