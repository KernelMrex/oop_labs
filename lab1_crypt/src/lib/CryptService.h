#ifndef CRYPT_SERVICE_H
#define CRYPT_SERVICE_H

#include <iostream>
#include <utility>

class CryptService
{
public:
	bool static Encrypt(std::istream& in, std::ostream& out, unsigned char keyByte)
	{
		unsigned char inByte, outByte;

		in >> std::noskipws;
		while ((in >> inByte) && out)
		{
			outByte = inByte ^ keyByte;

			out << (char) (
				GetAndMoveBit(outByte, 7, 5)
				| GetAndMoveBit(outByte, 6, 1)
				| GetAndMoveBit(outByte, 5, 0)
				| GetAndMoveBit(outByte, 4, 7)
				| GetAndMoveBit(outByte, 3, 6)
				| GetAndMoveBit(outByte, 2, 4)
				| GetAndMoveBit(outByte, 1, 3)
				| GetAndMoveBit(outByte, 0, 2)
			);
		}

		return !(!in.eof() && !in.good() || !out);
	}

	bool static Decrypt(std::istream& in, std::ostream& out, unsigned char keyByte)
	{
		unsigned char inByte, outByte;

		while ((in >> inByte) && out)
		{
			outByte = GetAndMoveBit(inByte, 5, 7)
				| GetAndMoveBit(inByte, 1, 6)
				| GetAndMoveBit(inByte, 0, 5)
				| GetAndMoveBit(inByte, 7, 4)
				| GetAndMoveBit(inByte, 6, 3)
				| GetAndMoveBit(inByte, 4, 2)
				| GetAndMoveBit(inByte, 3, 1)
				| GetAndMoveBit(inByte, 2, 0);

			out << (char) (outByte ^ keyByte);
		}

		return !(!in.eof() && !in.good() || !out);
	}

private:
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
