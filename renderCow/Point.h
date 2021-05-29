#pragma once
#include"MyVector.h"

class Point
{
public:
	double x;
	double y;
	double z;
	Point() {};
	Point(double x1, double y1, double z1) { x = x1; y = y1; z = z1; };
	Point operator+(const MyVector vec);
};

