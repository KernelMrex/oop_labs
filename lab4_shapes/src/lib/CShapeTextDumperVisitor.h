#ifndef CSHAPETEXTDUMPER_H
#define CSHAPETEXTDUMPER_H

#include "IShapeVisitor.h"
#include <ostream>

class CShapeTextDumperVisitor : public IShapeVisitor
{
public:
	explicit CShapeTextDumperVisitor(std::ostream& out);

	void VisitRectangle(const CRectangle& rectangle) override;

	void VisitCircle(const CCircle& circle) override;

	void VisitTriangle(const CTriangle& triangle) override;

	void VisitLineSegment(const CLineSegment& lineSegment) override;

private:
	std::ostream& m_out;
};

#endif // CSHAPETEXTDUMPER_H
