#include <iostream>
#include "MyVector.h"
#include "Triangle.h"
#include "Screen.h"
#include "Parser.h"
#include "Picture.h"
#include "OctoTree.h"

Point getCenter(vector<Point> points);

int main()
{
	Parser parser;
	std::vector<Point> points;
	std::vector<Triangle> tr = parser.parseFile("cow.obj", points);
	Point light(1, 1, 1);
	Point camera(0, -1, 0);
	Point point(0, 0, 1);
	Triangle triangle(Point(0, 0, 1), Point(1, 0, 0), Point(0, 1, 0));
	MyVector a(camera, getCenter(points));
	double dist = 4.5;
	Screen screen(a, camera, dist);
	//double** photo;
	//photo = screen.getPhoto(tr, camera, light);
	

	/*for (int i = 0; i < screen.height; i++)
	{
		for (int j = 0; j < screen.width; j++)
			std::cout << screen.points[i][j].x << " " << screen.points[i][j].y << " " << screen.points[i][j].z << " " << i << " " << j << "\n";
	}
	Picture pic;
	pic.write_picture("D:\\mybmp.bmp", photo, screen.pixels, screen.pixels);*/
	Box box(Point(-10,-10,-10), Point(10,10,10));
	//Box box1(Point(0, 0, 0), Point(10, 10, 10));
	//Triangle tr12(Point(0, 0, 1), Point(0, 1, 0), Point(1, 0, 0));
	OctoTree oct(box, tr);
	double** res = new double* [screen.pixels];
	for (int i = 0; i < screen.pixels; i++)
		res[i] = new double[screen.pixels];
	Point minPoint;
	for (int i = 0; i < screen.pixels; i++)
	{
		for (int j = 0; j < screen.pixels; j++)
		{
			double min = 1000;
			Triangle minTriangle;
			bool flag = false;
			oct.findMinIntersection(screen.points[i][j], camera, a, minTriangle, min, oct.root);
			if (min!=1000)
			{
				MyVector toSun(screen.points[i][j], light);
				MyVector n = MyVector::cross(MyVector(minTriangle.v1, minTriangle.v2), MyVector(minTriangle.v1, minTriangle.v3));
				res[i][j] = abs(MyVector::dot(toSun, n)) / (n.getLength() * toSun.getLength());
				//res[i][j] = 1;
			}
			else
				res[i][j] = 0;
		}
	}
	Picture pic;
	pic.write_picture("D:\\mybmp.bmp", res, screen.pixels, screen.pixels);
}

Point getCenter(vector<Point> points)
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