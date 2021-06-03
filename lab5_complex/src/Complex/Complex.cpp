#include "Complex.h"

#include <cfloat>
#include <cmath>

Complex::Complex(const Complex& complex) = default;

Complex::Complex(Complex&& complex) noexcept = default;

Complex::Complex(double real, double image)
	: m_real(real)
	, m_image(image)
{
}

double Complex::Re() const
{
	return m_real;
}

double Complex::Im() const
{
	return m_image;
}

double Complex::GetMagnitude() const
{
	return std::abs(m_real);
}

double Complex::GetArgument() const
{
	return std::abs(m_image);
}

Complex Complex::operator+() const
{
	return Complex(m_real, m_image);
}

Complex Complex::operator-() const
{
	return Complex(-m_real, -m_image);
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
	left.m_real += right.m_real;
	left.m_image += right.m_image;
	return left;
}

Complex& operator-=(Complex& left, const Complex& right)
{
	left.m_real -= right.m_real;
	left.m_image -= right.m_image;
	return left;
}

Complex& operator*=(Complex& left, const Complex& right)
{
	auto real = left.m_real * right.m_real - left.m_image * right.m_image;
	left.m_image = left.m_real * right.m_image + left.m_image * right.m_real;
	left.m_real = real;
	return left;
}

Complex& operator/=(Complex& left, const Complex& right)
{
	auto real = (left.m_real * right.m_real + left.m_image * right.m_image) / (right.m_real * right.m_real + right.m_image * right.m_image);
	left.m_image = (right.m_real * left.m_image - left.m_real * right.m_image) / (right.m_real * right.m_real + right.m_image * right.m_image);
	left.m_real = real;
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
	bool realNotZero = complex.m_real != 0;
	bool imageNotZero = complex.m_image != 0;

	if (realNotZero)
	{
		out
			<< ((complex.m_real > 0) ? "" : "-")
			<< complex.GetMagnitude();
	}

	if (imageNotZero && realNotZero)
	{
		out
			<< ((complex.m_image > 0) ? '+' : '-')
			<< complex.GetArgument()
			<< 'i';
	}

	if (imageNotZero && !realNotZero)
	{
		out
			<< ((complex.m_image > 0) ? "" : "-")
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
	in >> complex.m_real >> sign >> image;
	complex.m_image = (sign == '-') ? -image : image;
	in.ignore(1);
	return in;
}
