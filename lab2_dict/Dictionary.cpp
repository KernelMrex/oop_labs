#include <fstream>
#include "Dictionary.h"

// Constructors
Dictionary::~Dictionary() = default;

Dictionary::Dictionary(const std::string& path) {
    std::ifstream inputFile;

    // Open file
    inputFile.open(path);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Couldn't open dictionary file");
    }

    /* File:
    - кошка cat
    - cat вырезать
    */
}


// Methods
std::optional<std::string> Dictionary::Translate(const std::string& phrase) {
    return {""};
}

void Dictionary::SaveDict() {

}
