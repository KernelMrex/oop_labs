#include "lib/CHttpUrl/CHttpUrl.h"
#include "lib/CHttpUrl/Exception/CUrlParsingError.h"
#include "lib/http_utils.h"
#include <cstdlib>
#include <iostream>

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			CHttpUrl url(line);
			DumpHttpUrl(std::cout, url);
		}
		catch (CUrlParsingError& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	return EXIT_SUCCESS;
}