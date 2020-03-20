#include <iostream>
#include "encode.h"

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