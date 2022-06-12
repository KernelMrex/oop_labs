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
}