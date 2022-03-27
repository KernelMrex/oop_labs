#ifndef CRYPT_SERVICE_H
#define CRYPT_SERVICE_H

#include <iostream>
#include <utility>
#include <unordered_map>

class CryptService
{
public:
	explicit CryptService(unsigned char keyByte)
	{
		unsigned char swappedBitsToDecryptByte, xoredByteToEncrypt;

		for (int i = 0; i <= 255; i++)
		{
			swappedBitsToDecryptByte = (unsigned char) (GetAndMoveBit(i, 5, 7)
				| GetAndMoveBit(i, 1, 6)
				| GetAndMoveBit(i, 0, 5)
				| GetAndMoveBit(i, 7, 4)
				| GetAndMoveBit(i, 6, 3)
				| GetAndMoveBit(i, 4, 2)
				| GetAndMoveBit(i, 3, 1)
				| GetAndMoveBit(i, 2, 0));
			m_decryptLookupTable[i] = swappedBitsToDecryptByte ^ keyByte;


			xoredByteToEncrypt = i ^ keyByte;
			m_encryptLookupTable[i] = (unsigned char) (GetAndMoveBit(xoredByteToEncrypt, 7, 5)
				| GetAndMoveBit(xoredByteToEncrypt, 6, 1)
				| GetAndMoveBit(xoredByteToEncrypt, 5, 0)
				| GetAndMoveBit(xoredByteToEncrypt, 4, 7)
				| GetAndMoveBit(xoredByteToEncrypt, 3, 6)
				| GetAndMoveBit(xoredByteToEncrypt, 2, 4)
				| GetAndMoveBit(xoredByteToEncrypt, 1, 3)
				| GetAndMoveBit(xoredByteToEncrypt, 0, 2));
		}
	}

	bool Encrypt(std::istream& in, std::ostream& out)
	{
		unsigned char inByte;

		in >> std::noskipws;
		while ((in >> inByte) && out)
		{
			out << m_encryptLookupTable[inByte];
		}

		out.flush();

		return !(!in.eof() && !in.good() || !out);
	}

	bool Decrypt(std::istream& in, std::ostream& out)
	{
		unsigned char inByte;

		while ((in >> inByte) && out)
		{
			out << m_decryptLookupTable[inByte];
		}

		out.flush();

		return !(!in.eof() && !in.good() || !out);
	}

private:
	std::unordered_map<unsigned char, unsigned char> m_encryptLookupTable{};
	std::unordered_map<unsigned char, unsigned char> m_decryptLookupTable{};

	/**
	 * @param in source byte
	 * @param from bit position in byte 0..7
	 * @param to bit position in byte 0..7
	 * @return byte with all 0 bits except one bit set to 1 in 'to' position
	 */
	static unsigned char GetAndMoveBit(unsigned char in, unsigned char from, unsigned char to)
	{
		if (from >= 8 || to >= 8)
		{
			throw std::invalid_argument("GetAndMoveBit 'from' and 'to' arguments must be in range [0..7]");
		}

		unsigned char res = (in & ((unsigned char) 1 << from));

		return (from > to) ? (res >> (from  - to)) : (res << (to - from));
	}
};

#endif // CRYPT_SERVICE_H
