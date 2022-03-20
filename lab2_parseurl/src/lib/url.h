#ifndef URL_H
#define URL_H

#include <string>
#include "Protocol.h"

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);

#endif
