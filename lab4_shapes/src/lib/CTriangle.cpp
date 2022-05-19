#include "CTriangle.h"
#include <cmath>
#include <iomanip>
#include <sstream>

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CTriangle::GetArea() const
{
	return std::abs(m_vertex1.x * m_vertex2.y
			   + m_vertex2.x * m_vertex3.y
			   + m_vertex3.x * m_vertex1.y
			   - m_vertex1.y * m_vertex2.x
			   - m_vertex2.y * m_vertex3.x
			   - m_vertex3.y * m_vertex1.x) / 2;
}

double CTriangle::GetPerimeter() const
{
	return sqrt(pow(m_vertex1.x - m_vertex2.x, 2) + pow(m_vertex1.y - m_vertex2.y, 2))
		 + sqrt(pow(m_vertex2.x - m_vertex3.x, 2) + pow(m_vertex2.y - m_vertex3.y, 2))
		 + sqrt(pow(m_vertex3.x - m_vertex1.x, 2) + pow(m_vertex3.y - m_vertex1.y, 2));
}

std::string CTriangle::ToString() const
{
	std::stringstream ss;
	ss << "triangle "
	   << m_vertex1.x << ' ' << m_vertex1.y << ' '
	   << m_vertex2.x << ' ' << m_vertex2.y << ' '
	   << m_vertex3.x << ' ' << m_vertex3.y << ' '
	   << "0x" << std::setfill('0') << std::setw(6) << std::hex << m_outlineColor << ' '
	   << "0x" << std::setfill('0') << std::setw(6) << std::hex << m_fillColor;
	return ss.str();
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::Accept(IShapeVisitor& visitor) const
{
	visitor.VisitTriangle(*this);
}
