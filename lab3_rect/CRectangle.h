#ifndef LAB3_RECT_CRECTANGLE_H
#define LAB3_RECT_CRECTANGLE_H

#include "Point2D.h"

class CRectangle
{
public:
	/* Constructors and destructor */
	CRectangle(const Point2D& anchor, int width, int height);

	CRectangle(int anchorX, int anchorY, int width, int height);

	~CRectangle();

	/* Methods */
	void Move(int dx, int dy);

	void Scale(int sx, int sy);

	bool Intersect(CRectangle const& other);

	/* Getters and setters */
	int GetLeft();

	int GetRight();

	int GetTop();

	int GetBottom();

	void SetAnchor(const Point2D& anchor);

	void SetWidth(int width);

	void SetHeight(int height);

	Point2D* GetAnchor();

	int GetWidth();

	int GetHeight();

private:
	Point2D anchorPoint{ 0, 0 };
	int width;
	int height;
};

#endif //LAB3_RECT_CRECTANGLE_H
