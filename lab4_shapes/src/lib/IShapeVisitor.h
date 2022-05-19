#ifndef ISHAPEVISITOR_H
#define ISHAPEVISITOR_H

class CRectangle;
class CCircle;
class CTriangle;
class CLineSegment;

class IShapeVisitor
{
public:
	virtual void VisitRectangle(const CRectangle& rectangle) = 0;

	virtual void VisitCircle(const CCircle& circle) = 0;

	virtual void VisitTriangle(const CTriangle& triangle) = 0;

	virtual void VisitLineSegment(const CLineSegment& lineSegment) = 0;
};

#endif // ISHAPEVISITOR_H
