#ifndef HTTP_UTILS_H
#define HTTP_UTILS_H

#include "CHttpUrl/CHttpUrl.h"
#include <ostream>

void DumpHttpUrl(std::ostream& out, const CHttpUrl& url);

#endif // HTTP_UTILS_H
