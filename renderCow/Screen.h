#pragma once
#include"Point.h"
#include"MyVector.h"
#include"Triangle.h"

class Screen
{
public:
	double a;
	double b;
	double c;
	double d;
	double height;
	double width;
	double dist;
	Point center;
	Point** points;
	MyVector up;
	MyVector right;
	Screen(MyVector dir, Point camera, double dist1);
	double triangle_intersection(Point point, Point camera, Triangle triangle);

};

