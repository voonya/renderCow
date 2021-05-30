#include "Box.h"

Box::Box(Point point1, Point point2)
{
	MyVector vector1(point1);
	MyVector vector2(point2);
	if (vector1.lenght() < vector2.lenght())
	{
		min.x = point1.x;
		min.y = point1.y;
		min.z = point1.z;

		max.x = point2.x;
		max.x = point2.x;
		max.x = point2.x;
	}
	else
	{
		min.x = point2.x;
		min.y = point2.y;
		min.z = point2.z;

		max.x = point1.x;
		max.x = point1.x;
		max.x = point1.x;
	}
}
