#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
public:
	Complex(double real = 0, double image = 0);

	[[nodiscard]] double Re() const;

	[[nodiscard]] double Im() const;

	[[nodiscard]] double GetMagnitude() const;

	[[nodiscard]] double GetArgument() const;

	friend Complex operator+(const Complex& left, const Complex& right);

	friend Complex operator-(const Complex& left, const Complex& right);

	friend Complex operator*(const Complex& left, const Complex& right);

	friend Complex operator/(const Complex& left, const Complex& right);

	friend Complex& operator+=(Complex& left, const Complex& right);

	friend Complex& operator-=(Complex& left, const Complex& right);

	friend Complex& operator*=(Complex& left, const Complex& right);

	friend Complex& operator/=(Complex& left, const Complex& right);

private:
	double real;
	double image;
};

#endif
