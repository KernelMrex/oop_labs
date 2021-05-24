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

Complex operator+(const Complex& left, const Complex& right)
{
	return Complex(left.real + right.real, left.image + right.image);
}
