#ifndef COMPLEX_H
#define COMPLEX_H

#include <ostream>

class Complex
{
public:
	Complex(double real = 0, double image = 0);

	Complex(const Complex& complex);

	Complex(Complex&& complex) noexcept;

	[[nodiscard]] double Re() const;

	[[nodiscard]] double Im() const;

	[[nodiscard]] double GetMagnitude() const;

	[[nodiscard]] double GetArgument() const;

	Complex operator+() const;

	Complex operator-() const;

	friend Complex operator+(const Complex& left, const Complex& right);

	friend Complex operator-(const Complex& left, const Complex& right);

	friend Complex operator*(const Complex& left, const Complex& right);

	friend Complex operator/(const Complex& left, const Complex& right);

	friend Complex& operator+=(Complex& left, const Complex& right);

	friend Complex& operator-=(Complex& left, const Complex& right);

	friend Complex& operator*=(Complex& left, const Complex& right);

	friend Complex& operator/=(Complex& left, const Complex& right);

	friend bool operator==(const Complex& left, const Complex& right);

	friend bool operator!=(const Complex& left, const Complex& right);

	friend std::ostream& operator<<(std::ostream& out, const Complex& complex);

private:
	double real;
	double image;
};

#endif
