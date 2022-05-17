#ifndef ISOLIDSHAPE_H
#define ISOLIDSHAPE_H

#include "IShape.h"

class ISolidShape : public IShape
{
public:
	[[nodiscard]]
	virtual uint32_t GetFillColor() const = 0;

	virtual ~ISolidShape() = default;
};

#endif // ISOLIDSHAPE_H
