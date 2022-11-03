#ifndef POINT_H
#define POINT_H
#define VX 1
#define VO 2
class Point
{
	int x, y, check;

public:
	Point();
	Point(int, int);
	bool setCheck(int);
	int getX();
	int getY();
	int getCheck();
	void setX(int);
	void setY(int);
};
#endif // POINT_H

