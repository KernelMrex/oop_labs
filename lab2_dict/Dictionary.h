#include <map>
#include <set>
#include <string>
#include <vector>

class Dictionary
{
public:
	Dictionary();

	~Dictionary();

	std::optional<std::set<std::string>> Translate(const std::string& phrase);

	std::optional<std::string> TranslateToString(const std::string& phrase);

	void AddTranslation(const std::string& phrase, const std::string& translation);

protected:
	const std::map<std::string, std::set<std::string>>& GetDict();

private:
	void AddOneWayTranslation(const std::string& phrase, const std::string& translation);

	std::map<std::string, std::set<std::string>> dict;
};