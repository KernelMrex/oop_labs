#include <sstream>
#include "../../../../catch.hpp"
#include "../../../src/lib/CryptService.h"

TEST_CASE("CryptService class must Encrypt or Decrypt", "[crypt_service]")
{
	SECTION("Encrypting with key")
	{
		std::stringstream iss, oss, res;

		iss << (char) 0b00000000 << (char) 0b11111111 << (char) 0b00110011 << (char) 0b11001100;
		res << (char) 0b01001011 << (char) 0b10110100 << (char) 0b11000110 << (char) 0b00111001;

		CryptService cryptService(0b01101010);
		cryptService.Encrypt(iss, oss);

		REQUIRE(oss.str() == res.str());
	}

	SECTION("Decrypting with key")
	{
		std::stringstream iss, oss, res;

		iss << (char) 0b01001011 << (char) 0b10110100 << (char) 0b11000110 << (char) 0b00111001;
		res << (char) 0b00000000 << (char) 0b11111111 << (char) 0b00110011 << (char) 0b11001100;

		CryptService cryptService(0b01101010);
		cryptService.Decrypt(iss, oss);

		REQUIRE(oss.str() == res.str());
	}
}