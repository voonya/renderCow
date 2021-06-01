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
	
	vector<Point> lights;
	lights.push_back(Point(1, -1, 1));

	Point camera(0, -1, 0);
	MyVector a(camera, Point::getCenter(points));
	double dist = 12.5;
	Screen screen(a, camera, dist);

	Box box(Point(-10,-10,-10), Point(10,10,10));
	OctoTree oct(box, tr);

	double** res = new double* [screen.pixelsH];
	for (int i = 0; i < screen.pixelsH; i++)
		res[i] = new double[screen.pixelsW];
	
	for (int i = 0; i < screen.pixelsH; i++)
	{
		for (int j = 0; j < screen.pixelsW; j++)
		{
			double min = 1000;
			Triangle minTriangle;
			
			oct.findMinIntersection(screen.points[i][j], MyVector(screen.points[i][j], camera).getOrt(), minTriangle, min, oct.root);
			if (min!=1000)
			{
				for (int k = 0; k < lights.size(); k++)
				{
					bool flag = false;
					Point q;
					MyVector vec = MyVector(screen.points[i][j], camera).getOrt() * min;
					q = vec + screen.points[i][j];

					MyVector toSun = MyVector(q, lights[k]).getOrt();
					oct.findIntersection(q, toSun, oct.root, minTriangle, flag);

					MyVector n = MyVector::cross(MyVector(minTriangle.v1, minTriangle.v2), MyVector(minTriangle.v1, minTriangle.v3));
					res[i][j] = max(abs(MyVector::dot(toSun, n)) / (n.getLength() * toSun.getLength()), res[i][j]);
					if (flag)
					{
						res[i][j] = res[i][j] * 0.6;
					}
				}
			}
			else
				res[i][j] = max(res[i][j], 0.0);
		}
	}
	unsigned int end = clock();
	cout << end - start << endl;

	Picture pic;
	pic.write_picture("D:\\mybmp.bmp", res, screen.pixelsH, screen.pixelsW);
}
