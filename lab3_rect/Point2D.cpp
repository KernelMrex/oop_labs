#include "Point2D.h"

Point2D::Point2D(int x, int y)
{
	this->SetX(x);
	this->SetY(y);
}

void Point2D::SetX(int x)
{
	this->x = (x > 0) ? x : 0;
}

int Point2D::GetX() const
{
	return this->x;
}

void Point2D::SetY(int y)
{
	this->y = (y > 0) ? y : 0;
}

int Point2D::GetY() const
{
	return this->y;
}
