#include <sstream>
#include "../../../../catch.hpp"
#include "../../../src/lib/UrlParser.h"

TEST_CASE("UrlParser class must parse url", "[url_parser]")
{
	SECTION("Parsing urls")
	{
		std::stringstream iss;
		Protocol proto;
		int port;
		std::string host;
		std::string document;
		bool res;

		res = UrlParser::ParseURL("https://test.com", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 443);
		REQUIRE(proto == Protocol::HTTPS);
		REQUIRE(host == "test.com");
		REQUIRE(document.empty());

		res = UrlParser::ParseURL("https://test.com/", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 443);
		REQUIRE(proto == Protocol::HTTPS);
		REQUIRE(host == "test.com");
		REQUIRE(document.empty());

		res = UrlParser::ParseURL("https://test.com/files/file", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 443);
		REQUIRE(proto == Protocol::HTTPS);
		REQUIRE(host == "test.com");
		REQUIRE(document == "files/file");

		res = UrlParser::ParseURL("ftp://test.com/files/file", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 21);
		REQUIRE(proto == Protocol::FTP);
		REQUIRE(host == "test.com");
		REQUIRE(document == "files/file");

		res = UrlParser::ParseURL("http://test.com/files/file", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 80);
		REQUIRE(proto == Protocol::HTTP);
		REQUIRE(host == "test.com");
		REQUIRE(document == "files/file");

		res = UrlParser::ParseURL("http://test/files/file", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 80);
		REQUIRE(proto == Protocol::HTTP);
		REQUIRE(host == "test");
		REQUIRE(document == "files/file");

		res = UrlParser::ParseURL("http://www.mysite.com/docs/document1.html?page=30&lang=en#title", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 80);
		REQUIRE(proto == Protocol::HTTP);
		REQUIRE(host == "www.mysite.com");
		REQUIRE(document == "docs/document1.html?page=30&lang=en#title");

		res = UrlParser::ParseURL("http://www.mysite.com:700/docs/document1.html?page=30&lang=en#title", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 700);
		REQUIRE(proto == Protocol::HTTP);
		REQUIRE(host == "www.mysite.com");
		REQUIRE(document == "docs/document1.html?page=30&lang=en#title");

		res = UrlParser::ParseURL("unsupported://www.mysite/docs/document1.html?page=30&lang=en#title", proto, port, host, document);
		REQUIRE(res == false);

		res = UrlParser::ParseURL("random string", proto, port, host, document);
		REQUIRE(res == false);

		res = UrlParser::ParseURL("http://test.com:99999/files/file", proto, port, host, document);
		REQUIRE(res == false);

		res = UrlParser::ParseURL("http://test.com:99999999999999/files/file", proto, port, host, document);
		REQUIRE(res == false);
	}
}