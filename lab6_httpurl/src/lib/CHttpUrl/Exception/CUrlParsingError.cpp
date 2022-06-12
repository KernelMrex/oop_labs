#include "CUrlParsingError.h"

CUrlParsingError::CUrlParsingError(const std::string& msg)
	: std::invalid_argument(msg)
{
}


CUrlParsingError CUrlParsingError::InvalidUrl()
{
	return CUrlParsingError(CUrlParsingError::INVALID_URL_MSG);
}

CUrlParsingError CUrlParsingError::InvalidProtocol()
{
	return CUrlParsingError(CUrlParsingError::INVALID_PROTOCOL_MSG);
}

CUrlParsingError CUrlParsingError::InvalidPort()
{
	return CUrlParsingError(CUrlParsingError::INVALID_PORT_MSG);
}
