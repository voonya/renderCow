#include <iostream>
#include "MyVector.h"
#include "Point.h"
#include "Triangle.h"
#include "Screen.h"

int main()
{
	Point camera(0, 0, 0);
	MyVector a(1, 1, 1);
	double dist = 1;
	Screen screen(a, camera, dist);
	//std::cout << screen.right.x << " " << screen.right.y << " " << screen.right.z;
}