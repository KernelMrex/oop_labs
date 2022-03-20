#include <sstream>
#include "../../../../catch.hpp"
#include "../../../src/lib/url.h"

TEST_CASE("ParseURL must parse url", "[parse_url]")
{
	SECTION("Parsing urls")
	{
		std::stringstream iss;
		Protocol proto;
		int port;
		std::string host;
		std::string document;
		bool res;

		res = ParseURL("https://test.com", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 443);
		REQUIRE(proto == Protocol::HTTPS);
		REQUIRE(host == "test.com");
		REQUIRE(document.empty());

		res = ParseURL("https://test.com/", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 443);
		REQUIRE(proto == Protocol::HTTPS);
		REQUIRE(host == "test.com");
		REQUIRE(document.empty());

		res = ParseURL("https://test.com/files/file", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 443);
		REQUIRE(proto == Protocol::HTTPS);
		REQUIRE(host == "test.com");
		REQUIRE(document == "files/file");

		res = ParseURL("ftp://test.com/files/file", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 21);
		REQUIRE(proto == Protocol::FTP);
		REQUIRE(host == "test.com");
		REQUIRE(document == "files/file");

		res = ParseURL("http://test.com/files/file", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 80);
		REQUIRE(proto == Protocol::HTTP);
		REQUIRE(host == "test.com");
		REQUIRE(document == "files/file");

		res = ParseURL("http://test/files/file", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 80);
		REQUIRE(proto == Protocol::HTTP);
		REQUIRE(host == "test");
		REQUIRE(document == "files/file");

		res = ParseURL("http://www.mysite.com/docs/document1.html?page=30&lang=en#title", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 80);
		REQUIRE(proto == Protocol::HTTP);
		REQUIRE(host == "www.mysite.com");
		REQUIRE(document == "docs/document1.html?page=30&lang=en#title");

		res = ParseURL("http://www.mysite.com:700/docs/document1.html?page=30&lang=en#title", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 700);
		REQUIRE(proto == Protocol::HTTP);
		REQUIRE(host == "www.mysite.com");
		REQUIRE(document == "docs/document1.html?page=30&lang=en#title");

		res = ParseURL("unsupported://www.mysite/docs/document1.html?page=30&lang=en#title", proto, port, host, document);
		REQUIRE(res == false);

		res = ParseURL("random string", proto, port, host, document);
		REQUIRE(res == false);

		res = ParseURL("http://test.com:99999/files/file", proto, port, host, document);
		REQUIRE(res == false);

		res = ParseURL("http://test.com:99999999999999/files/file", proto, port, host, document);
		REQUIRE(res == false);
	}

	SECTION("Ports border values")
	{
		std::stringstream iss;
		Protocol proto;
		int port;
		std::string host;
		std::string document;
		bool res;

		res = ParseURL("https://test.com:0", proto, port, host, document);
		REQUIRE(res == false);

		res = ParseURL("https://test.com:1", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 1);
		REQUIRE(proto == Protocol::HTTPS);
		REQUIRE(host == "test.com");
		REQUIRE(document.empty());

		res = ParseURL("https://test.com:65535", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(port == 65535);
		REQUIRE(proto == Protocol::HTTPS);
		REQUIRE(host == "test.com");
		REQUIRE(document.empty());

		res = ParseURL("https://test.com:65536", proto, port, host, document);
		REQUIRE(res == false);
	}

	SECTION("Hostname length")
	{
		std::stringstream iss;
		Protocol proto;
		int port;
		std::string host;
		std::string document;
		bool res;

		res = ParseURL("https://t", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(host == "t");

		res = ParseURL("https://localhost", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(host == "localhost");

		res = ParseURL("https://localhost.localhost", proto, port, host, document);
		REQUIRE(res == true);
		REQUIRE(host == "localhost.localhost");
	}
}