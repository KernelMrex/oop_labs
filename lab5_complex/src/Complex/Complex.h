#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
public:
	explicit Complex(double real = 0, double image = 0);

	[[nodiscard]] double Re() const;

	[[nodiscard]] double Im() const;

	[[nodiscard]] double GetMagnitude() const;

	[[nodiscard]] double GetArgument() const;

private:
	double real;
	double image;
};

#endif
