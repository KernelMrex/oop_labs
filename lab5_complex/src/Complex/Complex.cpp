#include "Complex.h"

#include <cfloat>
#include <cmath>

Complex::Complex(const Complex& complex) = default;

Complex::Complex(Complex&& complex) noexcept = default;

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

Complex Complex::operator+() const
{
	return Complex(real, image);
}

Complex Complex::operator-() const
{
	return Complex(-real, -image);
}

Complex operator+(const Complex& left, const Complex& right)
{
	Complex result(left);
	return result += right;
}

Complex operator-(const Complex& left, const Complex& right)
{
	Complex result(left);
	return result -= right;
}

Complex operator*(const Complex& left, const Complex& right)
{
	Complex result(left);
	return result *= right;
}

Complex operator/(const Complex& left, const Complex& right)
{
	Complex result(left);
	return result /= right;
}

Complex& operator+=(Complex& left, const Complex& right)
{
	left.real += right.real;
	left.image += right.image;
	return left;
}

Complex& operator-=(Complex& left, const Complex& right)
{
	left.real -= right.real;
	left.image -= right.image;
	return left;
}

Complex& operator*=(Complex& left, const Complex& right)
{
	auto real = left.real * right.real - left.image * right.image;
	left.image = left.real * right.image + left.image * right.real;
	left.real = real;
	return left;
}

Complex& operator/=(Complex& left, const Complex& right)
{
	auto real = (left.real * right.real + left.image * right.image) / (right.real * right.real + right.image * right.image);
	left.image = (right.real * left.image - left.real * right.image) / (right.real * right.real + right.image * right.image);
	left.real = real;
	return left;
}

bool operator==(const Complex& left, const Complex& right)
{
	return (std::fabs(left.Re() - right.Re()) < DBL_EPSILON) && (std::fabs(left.Im() - right.Im()) < DBL_EPSILON);
}

bool operator!=(const Complex& left, const Complex& right)
{
	return !(left == right);
}

std::ostream& operator<<(std::ostream& out, const Complex& complex)
{
	bool realNotZero = complex.real != 0;
	bool imageNotZero = complex.image != 0;

	if (realNotZero)
	{
		out
			<< ((complex.real > 0) ? "" : "-")
			<< complex.GetMagnitude();
	}

	if (imageNotZero && realNotZero)
	{
		out
			<< ((complex.image > 0) ? '+' : '-')
			<< complex.GetArgument()
			<< 'i';
	}

	if (imageNotZero && !realNotZero)
	{
		out
			<< ((complex.image > 0) ? "" : "-")
			<< complex.GetArgument()
			<< 'i';
	}

	if (!imageNotZero && !realNotZero)
	{
		out << '0';
	}

	return out;
}

std::istream& operator>>(std::istream& in, Complex& complex)
{
	int image;
	char sign;
	in >> complex.real >> sign >> image;
	complex.image = (sign == '-') ? -image : image;
	in.ignore(1);
	return in;
}
