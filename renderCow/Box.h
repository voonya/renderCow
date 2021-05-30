#pragma once
#include "Point.h"
#include "MyVector.h"
class Box
{
	
public:
	Point min;
	Point max;
	Box() {};
	Box(Point min1, Point max1);
};

