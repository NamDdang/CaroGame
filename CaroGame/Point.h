#ifndef POINT_H
#define POINT_H
#include "Common.h"
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
