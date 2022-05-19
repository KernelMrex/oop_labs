#include "CLineSegment.h"
#include <cmath>
#include <iomanip>
#include <sstream>

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return sqrt(pow(m_startPoint.x - m_endPoint.x, 2) + pow(m_startPoint.y - m_endPoint.y, 2));
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::Accept(IShapeVisitor& visitor) const
{
	visitor.VisitLineSegment(*this);
}
