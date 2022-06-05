#ifndef SHAPEDRAWERVISITOR_H
#define SHAPEDRAWERVISITOR_H

#include "ICanvas.h"
#include "IShapeVisitor.h"

class ShapeDrawerVisitor : public IShapeVisitor
{
public:
	explicit ShapeDrawerVisitor(ICanvas& canvas);

	void VisitRectangle(const CRectangle& rectangle) final;

	void VisitCircle(const CCircle& circle) final;

	void VisitTriangle(const CTriangle& triangle) final;

	void VisitLineSegment(const CLineSegment& lineSegment) final;

private:
	ICanvas& m_canvas;
};

#endif // SHAPEDRAWERVISITOR_H
