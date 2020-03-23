#include "Dictionary.h"

class FileDictionary : public Dictionary
{
public:
	explicit FileDictionary(std::string path);

	~FileDictionary();

	void AddTranslation(const std::string& phrase, const std::string& translation);

	void Load();

	void Save();

	bool isSaved();

private:
	bool isSavedToFile;
	std::string path;
	void SaveDictToStream(std::ostream& out);
	void LoadDictFromStream(std::istream& in);
};
