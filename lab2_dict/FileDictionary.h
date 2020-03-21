#include "Dictionary.h"

class FileDictionary : public Dictionary {
public:
    explicit FileDictionary(std::string path);

    ~FileDictionary();

    void Load();

    void Save();

private:
    std::string path;
    void SaveDictToStream(std::ostream& out);
};
