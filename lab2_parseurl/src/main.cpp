#include "lib/UrlParser.h"
#include <iostream>

void DumpUrlData(const std::string& url, const Protocol& protocol, int port, const std::string& host, const std::string& document);

int main()
{
	std::string urlToParse;
	Protocol proto;
	int port;
	std::string host;
	std::string document;

	while (std::getline(std::cin, urlToParse))
	{
		if (urlToParse.empty())
		{
			return 0;
		}

		if (UrlParser::ParseURL(urlToParse, proto, port, host, document))
		{
			DumpUrlData(urlToParse, proto, port, host, document);
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Invalid url" << std::endl;
		}
	}

	if (!std::cin.eof() && std::cin.fail())
	{
		std::cout << "Error while reading" << std::endl;
		return 1;
	}

	return 0;
}

void DumpUrlData(const std::string& url, const Protocol& protocol, int port, const std::string& host, const std::string& document)
{
	std::cout
		<< "URL: " << url << std::endl
		<< "HOST: " << host << std::endl
		<< "PORT: " << port << std::endl
		<< "DOC: " << document << std::endl;
}
