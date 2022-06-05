#include "ShapeDrawerVisitor.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"

ShapeDrawerVisitor::ShapeDrawerVisitor(ICanvas& canvas)
	: m_canvas(canvas)
{
}

void ShapeDrawerVisitor::VisitRectangle(const CRectangle& rectangle)
{
	CPoint topLeft{ rectangle.GetLeftTop() },
		topRight{ rectangle.GetLeftTop().x + rectangle.GetWidth(), rectangle.GetLeftTop().y },
		bottomLeft{ rectangle.GetLeftTop().x, rectangle.GetLeftTop().y + rectangle.GetHeight() },
		bottomRight{ rectangle.GetLeftTop().x + rectangle.GetWidth(), rectangle.GetLeftTop().y + rectangle.GetHeight() };

	m_canvas.DrawPolygon(std::vector<CPoint>{
							 topLeft,
							 bottomLeft,
							 bottomRight,
							 topRight },
		rectangle.GetOutlineColor());

	m_canvas.FillPolygon(std::vector<CPoint>{
							 topLeft,
							 bottomLeft,
							 bottomRight,
							 topRight },
		rectangle.GetFillColor());
}

void ShapeDrawerVisitor::VisitCircle(const CCircle& circle)
{
	m_canvas.FillCircle(circle.GetCenter(), circle.GetRadius(), circle.GetFillColor());
	m_canvas.DrawCircle(circle.GetCenter(), circle.GetRadius(), circle.GetOutlineColor());
}

void ShapeDrawerVisitor::VisitTriangle(const CTriangle& triangle)
{
	m_canvas.FillPolygon(std::vector<CPoint>{
							 triangle.GetVertex1(),
							 triangle.GetVertex2(),
							 triangle.GetVertex3() },
		triangle.GetFillColor());
	m_canvas.DrawPolygon(std::vector<CPoint>{
							 triangle.GetVertex1(),
							 triangle.GetVertex2(),
							 triangle.GetVertex3() },
		triangle.GetOutlineColor());
}

void ShapeDrawerVisitor::VisitLineSegment(const CLineSegment& lineSegment)
{
	m_canvas.DrawLine(
		lineSegment.GetStartPoint(),
		lineSegment.GetEndPoint(),
		lineSegment.GetOutlineColor());
}
