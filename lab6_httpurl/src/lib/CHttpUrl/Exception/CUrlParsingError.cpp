#include "CUrlParsingError.h"

CUrlParsingError::CUrlParsingError(const std::string& msg)
	: std::invalid_argument(msg)
{
}

CUrlParsingError CUrlParsingError::InvalidUrl()
{
	return CUrlParsingError("Invalid url");
}

CUrlParsingError CUrlParsingError::InvalidProtocol()
{
	return CUrlParsingError("Invalid protocol");
}

CUrlParsingError CUrlParsingError::InvalidPort()
{
	return CUrlParsingError("Invalid port");
}

CUrlParsingError CUrlParsingError::InvalidDomain()
{
	return CUrlParsingError("Invalid domain");
}
