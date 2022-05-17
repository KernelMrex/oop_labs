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

std::string CLineSegment::ToString() const
{
	std::stringstream ss;
	ss << "line_segment "
	   << m_startPoint.x << ' ' << m_startPoint.y << ' '
	   << m_endPoint.x << ' ' << m_endPoint.y << ' '
	   << "0x" << std::setfill('0') << std::setw(6) << std::hex << m_outlineColor;
	return ss.str();
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
