#ifndef RLECOMPRESSOR_H
#define RLECOMPRESSOR_H

#include <iostream>

class RleCompressor final
{
public:
	RleCompressor() = delete;

	bool static Compress(std::istream& in, std::ostream& out)
	{
		unsigned char currByte;
		unsigned char prevState = 0;
		unsigned char counter = 0;
		bool isFirstChar = true;

		while ((in >> currByte) && out)
		{
			if (isFirstChar)
			{
				prevState = currByte;
				isFirstChar = false;
			}

			if (currByte == prevState)
			{
				if (counter >= 255)
				{
					out << counter << prevState;
					counter = 0;
				}
				counter++;
			}
			else
			{
				out << counter << prevState;
				counter = 1;
				prevState = currByte;
			}
		}

		if (!isFirstChar && out)
		{
			out << counter << prevState;
		}

		return !(!in.eof() && !in.good() || !out);
	}

	bool static Decompress(std::istream& in, std::ostream& out)
	{
		unsigned char amountOfBytes;
		unsigned char byte;

		while ((in >> amountOfBytes) && out)
		{
			if (!(in >> byte))
			{
				return false;
			}
			out << std::string(amountOfBytes, (char) byte);
		}

		return !(!in.eof() && !in.good() || !out);
	}

private:
	std::istream& in;
	std::ostream& out;
};

#endif // RLECOMPRESSOR_H
