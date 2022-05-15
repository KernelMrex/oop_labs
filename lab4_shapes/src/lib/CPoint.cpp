#include "CPoint.h"

CPoint::CPoint(double x, double y)
	: x(x)
	, y(y){}

bool CPoint::operator==(const CPoint& right) const
{
	return (x == right.x) && (y == right.y);
}
