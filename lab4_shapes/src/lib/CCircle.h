#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "CPoint.h"
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor);

	[[nodiscard]]
	double GetArea() const final;

	[[nodiscard]]
	double GetPerimeter() const final;

	[[nodiscard]]
	std::string ToString() const final;

	[[nodiscard]]
	uint32_t GetOutlineColor() const final;

	[[nodiscard]]
	uint32_t GetFillColor() const final;

	[[nodiscard]]
	CPoint GetCenter() const;

	[[nodiscard]]
	double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
	uint32_t m_outlineColor, m_fillColor;
};

#endif // CCIRCLE_H
