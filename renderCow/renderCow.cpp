#include <iostream>
#include "MyVector.h"
#include "Triangle.h"
#include "Screen.h"
#include "Picture.h"

int main()
{
	Point camera(0, 0, 0);
	Point point(0, 0, 1);
	Triangle triangle(Point(0, 0, 1), Point(1, 0, 0), Point(0, 1, 0));
	MyVector a(1, 1, 1);
	double dist = 1;
	Screen screen(a, camera, dist);
	/*for (int i = 0; i < screen.pixels; i++)
	{
		for (int j = 0; j < screen.pixels; j++)
			if (screen.triangle_intersection(screen.points[i][j], camera, triangle) != 0)
				std::cout << "@";
			else
				std::cout << ".";
		std::cout << "\n";
	}*/
	Picture pic;
	pic.write_picture("D:\\mybmp.bmp");
}