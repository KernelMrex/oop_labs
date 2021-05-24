#include "Complex.h"

#include <cmath>

Complex::Complex(double real, double image)
	: real(real)
	, image(image)
{
}

double Complex::Re() const
{
	return real;
}

double Complex::Im() const
{
	return image;
}

double Complex::GetMagnitude() const
{
	return std::abs(real);
}

double Complex::GetArgument() const
{
	return std::abs(image);
}
