#ifndef CHTTPURL_H
#define CHTTPURL_H

#include "Protocol.h"
#include <string>

class CHttpUrl
{
public:
	explicit CHttpUrl(const std::string& url);

    CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, uint16_t port);

	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol);

	[[nodiscard]]
	std::string GetURL() const;

	[[nodiscard]]
	Protocol GetProtocol() const;

	[[nodiscard]]
	std::string GetDomain() const;

	[[nodiscard]]
	uint16_t GetPort() const;

	[[nodiscard]]
	std::string GetDocument() const;

private:
	Protocol m_protocol;
	std::string m_domain;
	uint16_t m_port;
	std::string m_document;

	static Protocol ParseProtocol(const std::string& str);
	static uint16_t ParsePort(const std::string& str);
	static std::string NormalizeDocument(const std::string& str);
	static uint16_t GetDefaultPortForProtocol(Protocol protocol);
	static bool ValidateDomain(const std::string& str);
};

#endif // CHTTPURL_H
