#include "Point.h"

Point Point::operator+(const MyVector vec)
{
	Point point;
	point.x = x + vec.x;
	point.y = y + vec.y;
	point.z = z + vec.z;

	return point;
}
