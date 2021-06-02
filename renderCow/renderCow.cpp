#include <iostream>
#include "MyVector.h"
#include "Triangle.h"
#include "Screen.h"
#include "Parser.h"
#include "Picture.h"
#include "OctoTree.h"
#include <time.h>

int main()
{
	unsigned int start = clock();
	Parser parser;
	std::vector<Point> points;
	std::vector<Triangle> tr = parser.parseFile("cow.obj", points);
	
	/*vector<Point> lights;
	vector<Pixel_triplet> col;
	Pixel_triplet green;
	green.blueComponent = 0;
	green.redComponent = 0;
	green.greenComponent = 255;
	Pixel_triplet red;
	red.blueComponent = 0;
	red.redComponent = 255;
	red.greenComponent = 0;
	//col.push_back(green);
	col.push_back(red);
	Pixel_triplet blue;
	blue.blueComponent = 255;
	blue.redComponent = 0;
	blue.greenComponent = 0;
	
	col.push_back(blue);
	vector<double**> colors;
	lights.push_back(Point(1, -1, 1));
	lights.push_back(Point(-1, -1, 1));*/
	//lights.push_back(Point(1, 2, 1));
	//lights.push_back(Point(-1, -1, 1));
	vector<double**> colors;
	Point camera(1, -1, 0.4);
	Triangle triangle(Point(0, 0, 1), Point(1, 0, 0), Point(0, 1, 0));
	MyVector a(camera, Point::getCenter(points));
	double dist = 10.5;
	Screen screen(a, camera, dist);

	Box box(Point(-10,-10,-10), Point(10,10,10));
	OctoTree oct(box, tr);
	for (int k = 0; k < 3; k++)
	{
		double** res = new double* [screen.pixelsH];
		colors.push_back(res);
		for (int i = 0; i < screen.pixelsH; i++)
			colors[k][i] = new double[screen.pixelsW];
	}
	Point minPoint;
	cout << "start" << endl;
	
	for (int i = 0; i < screen.pixelsH; i++)
	{
		for (int j = 0; j < screen.pixelsW; j++)
		{
			double min = 1000;
			Triangle minTriangle;
			
			oct.findMinIntersection(screen.points[i][j], MyVector(screen.points[i][j], camera).getOrt(), minTriangle, min, oct.root);
			if (min!=1000)
			{
				for (int k = 0; k < 3; k++)
				{
					bool flag = false;

					Point q;
					MyVector vec = MyVector(screen.points[i][j], camera).getOrt() * min;
					q = vec + screen.points[i][j];

					//MyVector toSun = MyVector(q, lights[k]).getOrt();
					Triangle triangle;
					double min1 = 1000;
					//oct.findIntersection(q, toSun, oct.root, minTriangle, flag);
					MyVector n = MyVector::cross(MyVector(minTriangle.v1, minTriangle.v2), MyVector(minTriangle.v1, minTriangle.v3)).getOrt();
					colors[0][i][j] = abs(n.x);
					colors[1][i][j] = abs(n.y);
					colors[2][i][j] = abs(n.z);
					/*if (flag)
					{
						colors[k][i][j] = colors[k][i][j] * 0.7;
					}*/
						
				}
			}
			else
				for (int k = 0; k < 3; k++)
					colors[k][i][j] = 0;
		}
	}
	unsigned int end = clock();
	cout << end - start << endl;
	Picture pic;
	pic.write_picture("D:\\mybmp.bmp", colors, screen.pixelsH, screen.pixelsW);
}

