#ifndef PARSEURL_H
#define PARSEURL_H

#include "Protocol.h"
#include <regex>
#include <string>

class UrlParser
{
public:
	bool static ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
	{
		std::regex regex(R"(^(https|http|ftp)\:\/\/(\w+\.?(\w+\.)*\w+)\:?(\d{1,5})?\/?([\w\.\?\=\/\d\&\#]*)$)");
		std::smatch matches;

		if (std::regex_search(url, matches, regex))
		{
			try
			{
				protocol = ParseProtocol(matches[1]);
				host = matches[2];
				port = ParsePort(matches[4], protocol);
				document = matches[5];
			}
			catch (const std::logic_error&)
			{
				return false;
			}
			return true;
		}

		return false;
	}

private:
	Protocol static ParseProtocol(const std::string& protocol)
	{
		if (protocol == "http")
		{
			return Protocol::HTTP;
		}
		else if (protocol == "https")
		{
			return Protocol::HTTPS;
		}
		else if (protocol == "ftp")
		{
			return Protocol::FTP;
		}

		throw std::logic_error("Unsupported protocol");
	}

	int static ParsePort(const std::string& rawPort, const Protocol& protocol)
	{
		if (rawPort.empty())
		{
			return MapProtocolToDefaultPort(protocol);
		}

		int port;
		try
		{
			port = std::stoi(rawPort);
		}
		catch (std::invalid_argument const&)
		{
			throw std::logic_error("Port must be a number in range 0..65535");
		}
		catch (std::out_of_range const&)
		{
			throw std::out_of_range("Port must be in range 0..65535");
		}

		if (port <= 0 || port > 65535)
		{
			throw std::out_of_range("Port must be in range 0..65535");
		}

		return port;
	}

	int static MapProtocolToDefaultPort(const Protocol& protocol)
	{
		switch (protocol)
		{
		case Protocol::HTTPS:
			return 443;
		case Protocol::HTTP:
			return 80;
		case Protocol::FTP:
			return 21;
		}

		throw std::logic_error("Unsupported protocol");
	}
};

#endif // PARSEURL_H
