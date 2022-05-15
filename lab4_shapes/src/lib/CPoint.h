#ifndef CPOINT_H
#define CPOINT_H

#include <string>

class CPoint
{
public:
	double x;
	double y;

	CPoint(double x, double y);

	bool operator==(const CPoint& right) const;
};

#endif // CPOINT_H
