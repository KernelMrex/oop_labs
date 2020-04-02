#include "CRectangle.h"
#include <algorithm>

/* Constructors and destructor */
CRectangle::CRectangle(int anchorX, int anchorY, int width, int height)
{
	this->SetAnchorX(anchorX);
	this->SetAnchorY(anchorY);
	this->SetWidth(width);
	this->SetHeight(height);
}

CRectangle::~CRectangle() = default;

/* Methods */
bool CRectangle::Intersect(CRectangle const& other)
{
	int left = std::max(this->GetLeft(), other.GetLeft());
	int top = std::max(this->GetTop(), other.GetTop());
	int right = std::min(this->GetRight(), other.GetRight());
	int bottom = std::min(this->GetBottom(), other.GetBottom());
	return right - left >= 0 && bottom - top >= 0;
}

// TODO
void CRectangle::Scale(int sx, int sy)
{
}

// TODO
void CRectangle::Move(int dx, int dy)
{
}

/* Setters and Getters */
void CRectangle::SetAnchorX(int x)
{
	this->anchorPoint.SetX(x);
}

void CRectangle::SetAnchorY(int y)
{
	this->anchorPoint.SetY(y);
}

void CRectangle::SetWidth(int width)
{
	this->width = (width > 0) ? width : 0;
}

void CRectangle::SetHeight(int height)
{
	this->height = (height > 0) ? height : 0;
}

int CRectangle::GetWidth() const
{
	return this->width;
}

int CRectangle::GetHeight() const
{
	return this->height;
}

int CRectangle::GetLeft() const
{
	return this->anchorPoint.GetX();
}

int CRectangle::GetRight() const
{
	if (this->GetWidth() == 0)
	{
		return this->anchorPoint.GetX();
	}
	return this->anchorPoint.GetX() + this->GetWidth() - 1;
}

int CRectangle::GetTop() const
{
	return this->anchorPoint.GetY();
}

int CRectangle::GetBottom() const
{
	if (this->GetHeight() == 0)
	{
		return this->anchorPoint.GetY();
	}
	return this->anchorPoint.GetY() + this->GetHeight() - 1;
}
