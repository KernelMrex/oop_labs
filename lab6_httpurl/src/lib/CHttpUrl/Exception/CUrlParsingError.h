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
	inline static const std::string INVALID_URL_MSG = "Invalid url"; // NOLINT(cert-err58-cpp)
	inline static const std::string INVALID_PROTOCOL_MSG = "Invalid protocol"; // NOLINT(cert-err58-cpp)
	inline static const std::string INVALID_PORT_MSG = "Invalid port"; // NOLINT(cert-err58-cpp)
	inline static const std::string INVALID_DOMAIN_MSG = "Invalid domain"; // NOLINT(cert-err58-cpp)

	explicit CUrlParsingError(const std::string& msg);
};

#endif // CURLPARSINGERROR_H
