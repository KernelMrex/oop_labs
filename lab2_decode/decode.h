#include <memory>
#include <map>

struct Window {
    std::shared_ptr<char[]> content;
    int size;

    Window(int size) : size(size) {
        content = std::shared_ptr<char[]>(new char[size]);
        for (int i = 0; i < size; i++) {
            content[i] = 0;
        }
    }
};

typedef std::map<std::string, char> Dictionary;

std::string HtmlDecode(const std::string& html);

void HtmlDecode(std::istream& in, std::ostream& out, const Dictionary& chars);

void PushNextToDecoder(Window& window, char ch, const Dictionary& dict, std::ostream& out);

std::optional<int> DetermineMaxKeyLength(const Dictionary& chars);

std::optional<char> MoveWindow(Window& window, char ch);

std::optional<char> GetReplace(Window& window, const Dictionary& dict);

bool isWordInWindow(const Window& window, const std::string& word);
