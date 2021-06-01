#include <iostream>
#include "MyVector.h"
#include "Triangle.h"
#include "Screen.h"
#include "Parser.h"
#include "Picture.h"
#include "OctoTree.h"
#include <time.h>
Point getCenter(vector<Point> points);

int main()
{
	unsigned int start = clock();
	Parser parser;
	std::vector<Point> points;
	std::vector<Triangle> tr = parser.parseFile("cow.obj", points);
	Point light(0, 1, 0);
	Point camera(0, 0, 1);
	Point point(0, 0, 1);
	Triangle triangle(Point(0, 0, 1), Point(1, 0, 0), Point(0, 1, 0));
	MyVector a(camera, getCenter(points));
	double dist = 4.5;
	Screen screen(a, camera, dist);
	//double** photo;
	//photo = screen.getPhoto(tr, camera, light);
	

	 /*or (int i = 0; i < screen.height; i++)
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
	double** res = new double* [screen.pixelsH];
	for (int i = 0; i < screen.pixelsH; i++)
		res[i] = new double[screen.pixelsW];
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
				bool flag = false;
				//cout << endl << endl;
				Point q;
				MyVector vec = MyVector(screen.points[i][j], camera).getOrt() * min;
				q = vec + screen.points[i][j];

				MyVector toSun = MyVector(q, light).getOrt();
				//MyVector toSun = MyVector(light, q).getOrt();
				Triangle triangle;
				double min1 = 1000;
				//cout << toSun.x << " " << toSun.y << " " << toSun.z << " ";
				oct.findIntersection(q, toSun, oct.root, minTriangle, flag);
				//oct.findMinIntersection(light, toSun, triangle, min1, oct.root);
				//cout << flag << endl;
				if (!flag)
				//if (minTriangle.isEqual(triangle))
				{				
					MyVector n = MyVector::cross(MyVector(minTriangle.v1, minTriangle.v2), MyVector(minTriangle.v1, minTriangle.v3));
					res[i][j] = abs(MyVector::dot(toSun, n)) / (n.getLength() * toSun.getLength());
					//res[i][j] = 1;
				}
				else
					res[i][j] = 0;
			}
			else
				res[i][j] = 0;
		}
	}
	unsigned int end = clock();
	cout << end - start << endl;
	Picture pic;
	pic.write_picture("D:\\mybmp.bmp", res, screen.pixelsH, screen.pixelsW);
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

float hit_sphere(MyVector center, float radius, MyVector dir, MyVector origin) {
	MyVector oc = origin - center;
	float a = MyVector::dot(dir, dir);
	float b = 2.0 * MyVector::dot(oc, dir);
	float c = MyVector::dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}