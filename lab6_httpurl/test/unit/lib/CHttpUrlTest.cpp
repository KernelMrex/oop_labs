#include "../../../../catch.hpp"
#include "../../../src/lib/CHttpUrl/CHttpUrl.h"
#include "../../../src/lib/CHttpUrl/Exception/CUrlParsingError.h"

TEST_CASE("CHttpUrlTest unit tests", "[CHttpUrlTest_unit_tests]")
{
	SECTION("CHttpUrl(std::string) constructor must construct only valid urls")
	{
		WHEN("Url is \"https://test.example.com:123/test.doc?alfa=beta#gamma\"")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://test.example.com:123/test.doc?alfa=beta#gamma"));
			CHttpUrl url("https://test.example.com:123/test.doc?alfa=beta#gamma");
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "test.example.com");
			REQUIRE(url.GetPort() == 123);
			REQUIRE(url.GetDocument() == "/test.doc?alfa=beta#gamma");
		}

		WHEN("Url is \"https://test.example.com/test.doc?alfa=beta#gamma\"")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://test.example.com/test.doc?alfa=beta#gamma"));
			CHttpUrl url("https://test.example.com/test.doc?alfa=beta#gamma");
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "test.example.com");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetDocument() == "/test.doc?alfa=beta#gamma");
		}

		WHEN("Url is \"https://test.example.com/\"")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://test.example.com/"));
			CHttpUrl url("https://test.example.com/");
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "test.example.com");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetDocument() == "/");
		}

		WHEN("Url is \"https://test.example.com\"")
		{
			REQUIRE_NOTHROW(CHttpUrl("https://test.example.com"));
			CHttpUrl url("https://test.example.com");
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "test.example.com");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetDocument() == "/");
		}

		WHEN("Url is \"http://test.example.com\"")
		{
			REQUIRE_NOTHROW(CHttpUrl("http://test.example.com"));
			CHttpUrl url("http://test.example.com");
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetDomain() == "test.example.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetDocument() == "/");
		}

		WHEN("Url is \"abc\"")
		{
			REQUIRE_THROWS_AS(CHttpUrl("abc"), CUrlParsingError);
		}

		WHEN("Url is \"unknown://abc\"")
		{
			REQUIRE_THROWS_AS(CHttpUrl("unknown://abc"), CUrlParsingError);
		}

		WHEN("Url is \"http://----\"")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://----"), CUrlParsingError);
		}

		WHEN("Url is \"http:///\"")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://----"), CUrlParsingError);
		}

		WHEN("Url is \"http://abc:99999999999/\"")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://abc:99999999999/"), CUrlParsingError);
		}

		WHEN("Url is \"http://abc:99999/\"")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://abc:99999/"), CUrlParsingError);
		}

		WHEN("Url is \"http://abc:0/\"")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://abc:0/"), CUrlParsingError);
		}

		WHEN("Url is \"http://abc:0abc/\"")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://abc:0/"), CUrlParsingError);
		}
	}

	SECTION("CHttpUrl(std::string domain, std::string document, Protocol protocol, uint16_t port) constructor must construct only valid urls")
	{
		WHEN("Url is \"https://test.example.com:123/test.doc?alfa=beta#gamma\"")
		{
			REQUIRE_NOTHROW(CHttpUrl("test.example.com", "test.doc?alfa=beta#gamma", Protocol::HTTPS, 123));
			CHttpUrl url("test.example.com", "test.doc?alfa=beta#gamma", Protocol::HTTPS, 123);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "test.example.com");
			REQUIRE(url.GetPort() == 123);
			REQUIRE(url.GetDocument() == "/test.doc?alfa=beta#gamma");
		}

		WHEN("Url is \"https://test.example.com:123/test.doc?alfa=beta#gamma\"")
		{
			REQUIRE_NOTHROW(CHttpUrl("test.example.com", "/test.doc?alfa=beta#gamma", Protocol::HTTPS, 123));
			CHttpUrl url("test.example.com", "/test.doc?alfa=beta#gamma", Protocol::HTTPS, 123);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "test.example.com");
			REQUIRE(url.GetPort() == 123);
			REQUIRE(url.GetDocument() == "/test.doc?alfa=beta#gamma");
		}

		WHEN("Url is \"http://----/test.doc?alfa=beta#gamma\"")
		{
			REQUIRE_THROWS_AS(CHttpUrl("----", "/test.doc?alfa=beta#gamma", Protocol::HTTPS, 123), CUrlParsingError);
		}

		WHEN("Url is \"http:///test.doc?alfa=beta#gamma\"")
		{
			REQUIRE_THROWS_AS(CHttpUrl("", "/test.doc?alfa=beta#gamma", Protocol::HTTPS, 123), CUrlParsingError);
		}
	}

	SECTION("CHttpUrl(std::string domain, std::string document, Protocol protocol) constructor must construct only valid urls")
	{
		WHEN("Url is \"https://test.example.com/test.doc?alfa=beta#gamma\"")
		{
			REQUIRE_NOTHROW(CHttpUrl("test.example.com", "test.doc?alfa=beta#gamma", Protocol::HTTPS));
			CHttpUrl url("test.example.com", "test.doc?alfa=beta#gamma", Protocol::HTTPS);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "test.example.com");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetDocument() == "/test.doc?alfa=beta#gamma");
		}

		WHEN("Url is \"https://test.example.com/test.doc?alfa=beta#gamma\"")
		{
			REQUIRE_NOTHROW(CHttpUrl("test.example.com", "/test.doc?alfa=beta#gamma", Protocol::HTTPS));
			CHttpUrl url("test.example.com", "/test.doc?alfa=beta#gamma", Protocol::HTTPS);
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "test.example.com");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetDocument() == "/test.doc?alfa=beta#gamma");
		}

		WHEN("Url is \"http://example.com\"")
		{
			REQUIRE_NOTHROW(CHttpUrl("example.com", "", Protocol::HTTP));
			CHttpUrl url("example.com", "", Protocol::HTTP);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetDomain() == "example.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetDocument() == "/");
		}

		WHEN("Url is \"http://----/test.doc?alfa=beta#gamma\"")
		{
			REQUIRE_THROWS_AS(CHttpUrl("----", "/test.doc?alfa=beta#gamma", Protocol::HTTPS), CUrlParsingError);
		}

		WHEN("Url is \"http:///test.doc?alfa=beta#gamma\"")
		{
			REQUIRE_THROWS_AS(CHttpUrl("", "/test.doc?alfa=beta#gamma", Protocol::HTTPS), CUrlParsingError);
		}
	}

	SECTION("GetURL must provide valid url")
	{
		WHEN("Url is \"http://example.com\"")
		{
			CHttpUrl url("http://example.com");
			REQUIRE(url.GetURL() == "http://example.com/");
		}

		WHEN("Url is \"https://example.com\"")
		{
			CHttpUrl url("https://example.com");
			REQUIRE(url.GetURL() == "https://example.com/");
		}

		WHEN("Url is \"http://example.com:123\"")
		{
			CHttpUrl url("http://example.com:123");
			REQUIRE(url.GetURL() == "http://example.com:123/");
		}

		WHEN("Url is \"https://example.com:321\"")
		{
			CHttpUrl url("https://example.com:321");
			REQUIRE(url.GetURL() == "https://example.com:321/");
		}

		WHEN("Url is \"https://test.example.com:123/test.doc?alfa=beta#gamma\"")
		{
			CHttpUrl url("https://test.example.com:123/test.doc?alfa=beta#gamma");
			REQUIRE(url.GetURL() == "https://test.example.com:123/test.doc?alfa=beta#gamma");
		}
	}
}