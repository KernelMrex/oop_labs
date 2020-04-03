#ifndef LAB3_RECT_CRECTANGLE_H
#define LAB3_RECT_CRECTANGLE_H

#include "Point2D.h"

class CRectangle
{
public:
	/* Constructors and destructor */
	CRectangle(int anchorX, int anchorY, int width, int height);

	~CRectangle();

	/* Methods */
	void Move(int dx, int dy);

	void Scale(int sx, int sy);

	bool Intersect(CRectangle const& other);

	/* Getters and setters */
	int GetLeft() const;

	int GetRight() const;

	int GetTop() const;

	int GetBottom() const;

	void SetWidth(int width);

	void SetHeight(int height);

	int GetWidth() const;

	int GetHeight() const;

	void SetNewAnchorPos(int x, int y);

protected:
	const Point2D* GetAnchor() const;
	Point2D* GetAnchor();

private:
	Point2D anchorPoint{ 0, 0 };
	int width = 0;
	int height = 0;
};

#endif //LAB3_RECT_CRECTANGLE_H
