#include "CCircle.h"
#include <cmath>
#include <iomanip>
#include <stdexcept>

CCircle::CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	if (radius <= 0)
	{
		throw std::invalid_argument("CCircle must have positive radius");
	}
}

double CCircle::GetArea() const
{
	return M_PI * std::pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
	std::stringstream ss;
	ss << "circle "
	   << m_center.x << ' ' << m_center.y << ' '
	   << m_radius << ' '
	   << "0x" << std::setfill('0') << std::setw(6) << std::hex << m_outlineColor << ' '
	   << "0x" << std::setfill('0') << std::setw(6) << std::hex << m_fillColor;
	return ss.str();
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
