#include "CShapeTextDumperVisitor.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <iomanip>

CShapeTextDumperVisitor::CShapeTextDumperVisitor(std::ostream& out)
	: m_out(out)
{
}

void CShapeTextDumperVisitor::VisitRectangle(const CRectangle& rectangle)
{
	m_out << "rectangle "
		  << rectangle.GetLeftTop().x << ' ' << rectangle.GetLeftTop().y << ' '
		  << rectangle.GetWidth() << ' ' << rectangle.GetHeight() << ' '
		  << "0x" << std::setfill('0') << std::setw(6) << std::hex << rectangle.GetOutlineColor() << ' '
		  << "0x" << std::setfill('0') << std::setw(6) << std::hex << rectangle.GetFillColor();
}

void CShapeTextDumperVisitor::VisitCircle(const CCircle& circle)
{
	m_out << "circle "
		  << circle.GetCenter().x << ' ' << circle.GetCenter().y << ' '
		  << circle.GetRadius() << ' '
		  << "0x" << std::setfill('0') << std::setw(6) << std::hex << circle.GetOutlineColor() << ' '
		  << "0x" << std::setfill('0') << std::setw(6) << std::hex << circle.GetFillColor();
}

void CShapeTextDumperVisitor::VisitTriangle(const CTriangle& triangle)
{
	m_out << "triangle "
		  << triangle.GetVertex1().x << ' ' << triangle.GetVertex1().y << ' '
		  << triangle.GetVertex2().x << ' ' << triangle.GetVertex2().y << ' '
		  << triangle.GetVertex3().x << ' ' << triangle.GetVertex3().y << ' '
		  << "0x" << std::setfill('0') << std::setw(6) << std::hex << triangle.GetOutlineColor() << ' '
		  << "0x" << std::setfill('0') << std::setw(6) << std::hex << triangle.GetFillColor();
}

void CShapeTextDumperVisitor::VisitLineSegment(const CLineSegment& lineSegment)
{
	m_out << "line_segment "
	   << lineSegment.GetStartPoint().x << ' ' << lineSegment.GetStartPoint().y << ' '
	   << lineSegment.GetEndPoint().x << ' ' << lineSegment.GetEndPoint().y << ' '
	   << "0x" << std::setfill('0') << std::setw(6) << std::hex << lineSegment.GetOutlineColor();
}
