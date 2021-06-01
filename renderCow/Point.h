#pragma once
#include <vector>
using namespace std;
class Point
{
public:
	double x;
	double y;
	double z;
	Point() {};
	Point(double x1, double y1, double z1) { x = x1; y = y1; z = z1; };
	bool isEqual(Point p);
	static Point getCenter(vector<Point> points);
};

