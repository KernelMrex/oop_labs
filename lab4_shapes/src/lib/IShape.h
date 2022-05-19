#ifndef ISHAPE_H
#define ISHAPE_H

#include "IShapeVisitor.h"
#include <string>

class IShape
{
public:
	virtual ~IShape() = default;

	[[nodiscard]]
	virtual double GetArea() const = 0;

	[[nodiscard]]
	virtual double GetPerimeter() const = 0;

	[[nodiscard]]
	virtual uint32_t GetOutlineColor() const = 0;

	virtual void Accept(IShapeVisitor& visitor) const = 0;
};

#endif // ISHAPE_H
