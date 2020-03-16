#include <iostream>
#include <sstream>

std::string HtmlEncode(const std::string& text);

void HtmlEncode(std::istream& in, std::ostream& out);

int main()
{
	std::string line;
	while (std::cin.good())
	{
		std::getline(std::cin, line);

		std::string encodedHtml;
		try
		{
			encodedHtml = HtmlEncode(line);
		}
		catch (const std::exception& err)
		{
			std::cout << err.what() << std::endl;
			return 1;
		}
		std::cout << encodedHtml << std::endl;
	}

	return 0;
}

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
