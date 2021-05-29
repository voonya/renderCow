#pragma once
#include "Point.h"

class Triangle
{
public:
	Point v1;
	Point v2;
	Point v3;
	Triangle() {};
	Triangle(Point v11, Point v22, Point v33) { v1 = v11; v2 = v22; v3 = v33; };
};

