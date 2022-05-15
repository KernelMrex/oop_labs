#ifndef ISHAPE_H
#define ISHAPE_H

#include <string>

class IShape
{
public:
	virtual ~IShape() {}

	[[nodiscard]]
	virtual double GetArea() const = 0;

	[[nodiscard]]
	virtual double GetPerimeter() const = 0;

	[[nodiscard]]
	virtual std::string ToString() const = 0;

	[[nodiscard]]
	virtual uint32_t GetOutlineColor() const = 0;
};

#endif // ISHAPE_H
