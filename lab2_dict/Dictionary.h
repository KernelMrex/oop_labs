#include <string>
#include <map>
#include <vector>
#include <set>

class Dictionary {
public:
    Dictionary();

    ~Dictionary();

    std::optional<std::set<std::string>> Translate(const std::string& phrase);

    void AddTranslation(const std::string& phrase, const std::string& translation);

private:
    std::map<std::string, std::set<std::string>> dict;
};