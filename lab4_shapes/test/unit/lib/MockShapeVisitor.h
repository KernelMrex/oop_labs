#ifndef MOCKSHAPEVISITOR_H
#define MOCKSHAPEVISITOR_H

#include "../../../src/lib/IShapeVisitor.h"
#include <string>

class MockShapeVisitor : public IShapeVisitor
{
public:
	void VisitRectangle(const CRectangle& rectangle) override
	{
		m_visited = "rectangle";
	}

	void VisitCircle(const CCircle& circle) override
	{
		m_visited = "circle";
	}

	void VisitTriangle(const CTriangle& triangle) override
	{
		m_visited = "triangle";
	}

	void VisitLineSegment(const CLineSegment& lineSegment) override
	{
		m_visited = "line_segment";
	}

	std::string m_visited;
};

#endif // MOCKSHAPEVISITOR_H
