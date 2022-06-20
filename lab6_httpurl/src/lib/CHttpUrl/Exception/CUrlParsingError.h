#ifndef CURLPARSINGERROR_H
#define CURLPARSINGERROR_H

#include <stdexcept>
#include <string>

class CUrlParsingError : public std::invalid_argument, public std::nested_exception
{
public:
	static CUrlParsingError InvalidUrl();
	static CUrlParsingError InvalidProtocol();
	static CUrlParsingError InvalidPort();
	static CUrlParsingError InvalidDomain();

private:
	explicit CUrlParsingError(const std::string& msg);
};

#endif // CURLPARSINGERROR_H
