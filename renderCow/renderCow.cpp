#include <iostream>
#include "MyVector.h"
#include "Triangle.h"
#include "Screen.h"
#include "Parser.h"
#include "Picture.h"

int main()
{
	Parser parser;
	std::vector<Triangle> tr = parser.parseFile("s.obj");
	Point camera(0, 0, 0);
	Point point(0, 0, 1);
	Triangle triangle(Point(0, 0, 1), Point(1, 0, 0), Point(0, 1, 0));
	MyVector a(1, 1, 1);
	double dist = 1;
	Screen screen(a, camera, dist);
		for (int i = 0; i < screen.pixels; i++)
		{
			for (int j = 0; j < screen.pixels; j++) {
				bool flag = false;
				for (int k = 0; k < tr.size(); k++) {
					if (screen.triangle_intersection(screen.points[i][j], camera, tr[k]) != 0)
						flag = true;
				}
				if (flag) {
					std::cout << "@";
				}
				else
					std::cout << ".";
				
			}
			std::cout << "\n";
		}
	

	/*for (int i = 0; i < screen.height; i++)
	{
		for (int j = 0; j < screen.width; j++)
			std::cout << screen.points[i][j].x << " " << screen.points[i][j].y << " " << screen.points[i][j].z << " " << i << " " << j << "\n";
	}*/
	Picture pic;
	pic.write_picture("D:\\mybmp.bmp");
}