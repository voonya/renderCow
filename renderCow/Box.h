#pragma once
#include "Point.h"
#include "MyVector.h"
class Box
{
	Point min;
	Point max;
public:
	Box();
	Box(Point min1, Point max1);
	Point getMin()
};

