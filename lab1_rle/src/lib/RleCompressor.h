#ifndef RLECOMPRESSOR_H
#define RLECOMPRESSOR_H

#include <iostream>

class RleCompressor final
{
public:
	RleCompressor() = delete;

	bool static compress(std::istream& in, std::ostream& out)
	{
		unsigned char currByte;
		unsigned char prevState = 0;
		unsigned char counter = 0;
		bool first = true;

		while ((in >> currByte) && out)
		{
			if (first)
			{
				prevState = currByte;
				first = false;
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

		if (!first && out)
		{
			out << counter << prevState;
		}

		return !(!in.eof() && !in.good() || !out);
	}

	bool static decompress(std::istream& in, std::ostream& out)
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
