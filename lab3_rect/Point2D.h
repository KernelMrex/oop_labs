#ifndef LAB3_RECT_POINT2D_H
#define LAB3_RECT_POINT2D_H

class Point2D
{
public:
	Point2D(int x, int y);

	void SetX(int x);

	int GetX();

	void SetY(int y);

	int GetY();

private:
	int x;
	int y;
};

#endif //LAB3_RECT_POINT2D_H
