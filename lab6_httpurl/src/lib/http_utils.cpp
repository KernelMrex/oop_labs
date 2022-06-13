#include "http_utils.h"

void DumpHttpUrl(std::ostream& out, const CHttpUrl& url)
{
	out
		<< "Protocol: " << (url.GetProtocol() == Protocol::HTTP ? "http" : "https") << std::endl
		<< "Domain: " << url.GetDomain() << std::endl
		<< "Port: " << url.GetPort() << std::endl
		<< "Document: " << url.GetDocument() << std::endl;
}
