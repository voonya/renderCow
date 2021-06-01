#include "Point.h"

bool Point::isEqual(Point p)
{
	if ((p.x == x) && (p.y == y) && (p.z == z))
		return true;
	else
		return false;
}
