#include "string_utils.h"

template <class Container>
void split(const std::string& str, Container& cont, char delimiter)
{
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimiter)) {
		cont.push_back(token);
	}
}