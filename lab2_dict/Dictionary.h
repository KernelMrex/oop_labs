#include <string>
#include <map>
#include <vector>


class Dictionary {
public:
    explicit Dictionary(const std::string& path);
    ~Dictionary();

    std::optional<std::string> Translate(const std::string& phrase);
    void SaveDict();
private:
    const std::string dictPath;
    std::map<std::string, std::vector<std::string>> dict;
};