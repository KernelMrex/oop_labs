#include "CRectangle.h"

/* Constructors and destructor */
CRectangle::CRectangle(const Point2D& anchor, int width, int height)
{
	this->SetAnchor(anchor);
	this->SetWidth(width);
	this->SetHeight(height);
}

CRectangle::CRectangle(int anchorX, int anchorY, int width, int height)
{
	this->SetAnchor(Point2D{ anchorX, anchorY });
	this->SetWidth(width);
	this->SetHeight(height);
}

CRectangle::~CRectangle() = default;

/* Methods */
// TODO
bool CRectangle::Intersect(CRectangle const& other)
{
	return false;
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
void CRectangle::SetAnchor(const Point2D& anchor)
{
	this->anchorPoint = anchor;
}

void CRectangle::SetWidth(int width)
{
    this->width = (width > 0) ? width : 0;
}

void CRectangle::SetHeight(int height)
{
    this->height = (height > 0 && (this->GetAnchor()->GetY() - height) > 0) ? height : 0;
}

Point2D* CRectangle::GetAnchor()
{
	return &this->anchorPoint;
}

int CRectangle::GetWidth()
{
	return this->width;
}

int CRectangle::GetHeight()
{
	return this->height;
}

int CRectangle::GetLeft()
{
	return this->GetAnchor()->GetX();
}

int CRectangle::GetRight()
{
	return this->GetAnchor()->GetX() + this->GetWidth();
}

int CRectangle::GetTop()
{
	return this->GetAnchor()->GetY();
}

int CRectangle::GetBottom()
{
	return this->GetAnchor()->GetY() - this->GetHeight();
}