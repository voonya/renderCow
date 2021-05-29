#pragma once
#include"Point.h"

class MyVector
{
public:
	double x;
	double y;
	double z;
	MyVector() {};
	MyVector(Point point) { x = point.x; y = point.y; z = point.z; };
	MyVector(Point point1, Point point2) { x = point2.x - point1.x; y = point2.y - point1.y; z = point2.z - point1.z; };
	MyVector(double x1, double y1, double z1) { x = x1; y = y1; z = z1; };
	MyVector getOrt();
	static MyVector cross(MyVector vec1, MyVector vec2);
	static double dot(MyVector vec1, MyVector vec2);
	MyVector operator*(const double a);
	Point operator+(const Point point);
	MyVector operator+(const MyVector vec1);
	MyVector operator-(const MyVector vec1);
};

