#pragma once
#include"Point.h"
#include"MyVector.h"
#include"Triangle.h"
#include <vector>

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
	int pixelsW;
	int pixelsH;
	Point center;
	Point** points;
	MyVector up;
	MyVector right;
	Screen(MyVector dir, Point camera, double dist1);
	static double triangle_intersection(Point point, Point camera, Triangle triangle);
	static double triangle_intersection(Point point, MyVector dir, Triangle triangle);
	double** getPhoto(std::vector<Triangle> tr, Point camera, Point light);
};

