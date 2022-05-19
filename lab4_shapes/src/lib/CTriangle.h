#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CPoint.h"
#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor);

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
	CPoint GetVertex1() const;

	[[nodiscard]]
	CPoint GetVertex2() const;

	[[nodiscard]]
	CPoint GetVertex3() const;

	void Accept(IShapeVisitor& visitor) const final;

private:
	CPoint m_vertex1, m_vertex2, m_vertex3;
	uint32_t m_outlineColor, m_fillColor;
};

#endif // CTRIANGLE_H
