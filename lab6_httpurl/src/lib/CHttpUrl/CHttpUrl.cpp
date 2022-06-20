#include "CHttpUrl.h"
#include "Exception/CUrlParsingError.h"
#include <regex>

CHttpUrl::CHttpUrl(const std::string& url)
{
	static std::regex urlRegex(
		R"(^(https?)://((?:[a-zA-Z0-9][a-zA-Z0-9\-]+\.)*[a-zA-Z0-9][a-zA-Z0-9\-]+)(?:\:(\d{1,5}))?(\/.*)?$)"
		);

	std::smatch urlPartMatch;
	if (!std::regex_search(url, urlPartMatch, urlRegex))
	{
		throw CUrlParsingError::InvalidUrl();
	}

	m_protocol = ParseProtocol(urlPartMatch[1]);
	m_domain = urlPartMatch[2];
	m_port = urlPartMatch[3].str().empty() ? GetDefaultPortForProtocol(m_protocol) : ParsePort(urlPartMatch[3]);
	m_document = NormalizeDocument(urlPartMatch[4]);
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, uint16_t port)
{
	if (!ValidateDomain(domain))
	{
		throw CUrlParsingError::InvalidDomain();
	}
	m_domain = domain;

	m_document = NormalizeDocument(document);
	m_port = port;
	m_protocol = protocol;
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
{
	if (!ValidateDomain(domain))
	{
		throw CUrlParsingError::InvalidDomain();
	}
	m_domain = domain;
	m_document = NormalizeDocument(document);
	m_port = GetDefaultPortForProtocol(protocol);
	m_protocol = protocol;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

uint16_t CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::ParseProtocol(const std::string& str)
{
	if (str == "https")
	{
		return Protocol::HTTPS;
	}
	else if (str == "http")
	{
		return Protocol::HTTP;
	}

	throw CUrlParsingError::InvalidProtocol();
}

uint16_t CHttpUrl::ParsePort(const std::string& str)
{
	uint16_t res = 0;
	try
	{
		int intValue = std::stoi(str);
		if (intValue <= 0 || intValue >= 65536)
		{
			throw std::out_of_range("Value must be in range 1..65535");
		}
		res = intValue;
	}
	catch (const std::out_of_range& ex)
	{
        std::throw_with_nested(CUrlParsingError::InvalidPort());
	}
	catch (const std::invalid_argument& ex)
	{
		std::throw_with_nested(CUrlParsingError::InvalidPort());
	}

	return res;
}

std::string CHttpUrl::NormalizeDocument(const std::string& str)
{
	return str.starts_with("/") ? str : ("/" + str);
}

uint16_t CHttpUrl::GetDefaultPortForProtocol(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTPS:
		return 443;
	case Protocol::HTTP:
		return 80;
	}
}

bool CHttpUrl::ValidateDomain(const std::string& str)
{
	static std::regex domainRegex(R"(^(?:[a-zA-Z0-9][a-zA-Z0-9\-]+\.)*[a-zA-Z0-9][a-zA-Z0-9\-]+$)");
	return std::regex_match(str, domainRegex);
}

std::string CHttpUrl::GetURL() const
{
	std::stringstream ss;
	ss << (GetProtocol() == Protocol::HTTP ? "http" : "https") << "://" << GetDomain();
	if (GetDefaultPortForProtocol(GetProtocol()) != GetPort())
	{
		ss << ":" << GetPort();
	}
	ss << GetDocument();

	return ss.str();
}