
#include <sstream>
#include "encode.h"

std::string HtmlEncode(const std::string& text)
{
    std::istringstream in(text);
    std::ostringstream out;
    HtmlEncode(in, out);
    return out.str();
}

void HtmlEncode(std::istream& in, std::ostream& out)
{
    char ch;
    while (in >> std::noskipws >> ch)
    {
        switch (ch)
        {
            case '"':
                out << "&quot;";
                break;
            case '\'':
                out << "&apos;";
                break;
            case '>':
                out << "&gt;";
                break;
            case '<':
                out << "&lt;";
                break;
            case '&':
                out << "&amp;";
                break;
            default:
                out << ch;
        }
    }
    if (!in.eof() && in.fail())
    {
        throw std::runtime_error("error while reading");
    }
}
