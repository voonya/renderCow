#include "Point.h"

bool Point::isEqual(Point p)
{
	if ((p.x == x) && (p.y == y) && (p.z == z))
		return true;
	else
		return false;
}

Point Point::getCenter(vector<Point> points)
{
	Point center(0, 0, 0);
	for (int i = 0; i < points.size(); i++)
	{
		center.x = center.x + points[i].x;
		center.y = center.y + points[i].y;
		center.z = center.z + points[i].z;
	}
	center.x = center.x / points.size();
	center.y = center.y / points.size();
	center.z = center.z / points.size();
	return center;
}
