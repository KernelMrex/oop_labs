#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "CPoint.h"
#include "ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(const CPoint& topLeft, double width, double height, uint32_t outlineColor, uint32_t fillColor);

	[[nodiscard]]
	double GetArea() const final;

	[[nodiscard]]
	double GetPerimeter() const final;

	[[nodiscard]]
	uint32_t GetOutlineColor() const final;

	[[nodiscard]]
	uint32_t GetFillColor() const final;

	[[nodiscard]]
	CPoint GetLeftTop() const;

	[[nodiscard]]
	CPoint GetRightBottom() const;

	[[nodiscard]]
	double GetWidth() const;

	[[nodiscard]]
	double GetHeight() const;

	void Accept(IShapeVisitor& visitor) const final;

private:
	CPoint m_topLeft;
	double m_width, m_height;
	uint32_t m_outlineColor, m_fillColor;
};

#endif // CRECTANGLE_H
