#include "Point2D.h"

Point2D::Point2D(int x, int y)
	: x(x)
	, y(y)
{
}

void Point2D::SetX(int x)
{
	this->x = x;
}

int Point2D::GetX()
{
	return this->x;
}

void Point2D::SetY(int y)
{
	this->y = y;
}

int Point2D::GetY()
{
	return this->y;
}
