#include "CRectangle.h"
#include <iomanip>
#include <sstream>

CRectangle::CRectangle(const CPoint& topLeft, double width, double height, uint32_t outlineColor, uint32_t fillColor)
	: m_topLeft(topLeft)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	if (width <= 0 || height <= 0)
	{
		throw std::invalid_argument("CRectangle must have positive width and height");
	}
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return m_width * 2 + m_height * 2;
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_topLeft;
}

CPoint CRectangle::GetRightBottom() const
{
	return {m_topLeft.x + m_width, m_topLeft.y + m_height};
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::Accept(IShapeVisitor& visitor) const
{
	visitor.VisitRectangle(*this);
}
