#ifndef RLECOMPRESSOR_H
#define RLECOMPRESSOR_H

#include <iostream>

class RleCompressor final
{
public:
	RleCompressor(std::istream& in, std::ostream& out)
		: m_in(in)
		, m_out(out)
	{
	}

	bool compress()
	{
		unsigned char currByte;
		unsigned char prevState = 0;
		unsigned char counter = 0;
		bool first = true;

		while ((m_in >> currByte) && m_out)
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
					m_out << counter << prevState;
					counter = 0;
				}
				counter++;
			}
			else
			{
				m_out << counter << prevState;
				counter = 1;
				prevState = currByte;
			}
		}

		if (!first && m_out)
		{
			m_out << counter << prevState;
		}

		return !(!m_in.eof() && !m_in.good() || !m_out);
	}

	bool decompress()
	{
		return false;
	}

private:
	std::istream& m_in;
	std::ostream& m_out;
};

#endif // RLECOMPRESSOR_H
