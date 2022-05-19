#ifndef CLINESEGMENT_H
#define CLINESEGMENT_H

#include "CPoint.h"
#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor);

	[[nodiscard]]
	double GetArea() const final;

	[[nodiscard]]
	double GetPerimeter() const final;

	[[nodiscard]]
	uint32_t GetOutlineColor() const final;

	[[nodiscard]]
	CPoint GetStartPoint() const;

	[[nodiscard]]
	CPoint GetEndPoint() const;

	void Accept(IShapeVisitor& visitor) const final;

private:
	CPoint m_startPoint, m_endPoint;
	uint32_t m_outlineColor;
};

#endif // CLINESEGMENT_H
