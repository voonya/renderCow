#include <iostream>
#include "MyVector.h"
#include "Triangle.h"
#include "Screen.h"

int main()
{
	Point camera(0, 0, 0);
	Point point(0, 0, 1);
	Triangle triangle(Point(0, 0, 1), Point(1, 0, 0), Point(0, 1, 0));
	MyVector a(1, 1, 1);
	double dist = 1;
	Screen screen(a, camera, dist);
	for (int i = 0; i < screen.height; i++)
	{
		for (int j = 0; j < screen.width; j++)
			if (screen.triangle_intersection(screen.points[i][j], camera, triangle) != 0)
				std::cout << "@";
			else
				std::cout << ".";
		std::cout << "\n";
	}
	/*for (int i = 0; i < screen.height; i++)
	{
		for (int j = 0; j < screen.width; j++)
			std::cout << screen.points[i][j].x << " " << screen.points[i][j].y << " " << screen.points[i][j].z << " " << i << " " << j << "\n";
	}*/
	//std::cout << screen.center.x << " " << screen.center.y << " " << screen.center.z << "\n";
	 //std::cout << screen.triangle_intersection(screen.center, camera, triangle);
	//::cout << screen.triangle_intersection(point, camera, triangle);
	//std::cout << screen.right.x << " " << screen.right.y << " " << screen.right.z;
}