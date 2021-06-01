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
	
	vector<Point> lights;
	vector<Pixel_triplet> col;
	Pixel_triplet green;
	green.blueComponent = 0;
	green.redComponent = 0;
	green.greenComponent = 255;
	col.push_back(green);
	Pixel_triplet blue;
	blue.blueComponent = 255;
	blue.redComponent = 0;
	blue.greenComponent = 0;
	col.push_back(blue);
	vector<double**> colors;
	lights.push_back(Point(1, -1, 1));
	lights.push_back(Point(-1, -1, 1));
	//lights.push_back(Point(-1, -1, 1));
	Point camera(0, -1, 0);
	Triangle triangle(Point(0, 0, 1), Point(1, 0, 0), Point(0, 1, 0));
	MyVector a(camera, getCenter(points));
	double dist = 12.5;
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
	for (int k = 0; k < lights.size(); k++)
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
				for (int k = 0; k < lights.size(); k++)
				{
					bool flag = false;
					//cout << endl << endl;
					Point q;
					MyVector vec = MyVector(screen.points[i][j], camera).getOrt() * min;
					q = vec + screen.points[i][j];

					MyVector toSun = MyVector(q, lights[k]).getOrt();
					//MyVector toSun = MyVector(light, q).getOrt();
					Triangle triangle;
					double min1 = 1000;
					//cout << toSun.x << " " << toSun.y << " " << toSun.z << " ";
					oct.findIntersection(q, toSun, oct.root, minTriangle, flag);
					//oct.findMinIntersection(light, toSun, triangle, min1, oct.root);
					//cout << flag << endl;
					MyVector n = MyVector::cross(MyVector(minTriangle.v1, minTriangle.v2), MyVector(minTriangle.v1, minTriangle.v3));
					colors[k][i][j] = max(abs(MyVector::dot(toSun, n)) / (n.getLength() * toSun.getLength()), colors[k][i][j]);
					if (flag)
						//if (minTriangle.isEqual(triangle))
					{
						colors[k][i][j] = colors[k][i][j] * 0.7;
						//res[i][j] = 1;
					}
						
				}
			}
			else
				for (int k = 0; k < lights.size(); k++)
					colors[k][i][j] = max(colors[k][i][j], 0.0);
		}
	}
	unsigned int end = clock();
	cout << end - start << endl;
	Picture pic;
	pic.write_picture("D:\\mybmp.bmp", col, colors, screen.pixelsH, screen.pixelsW);
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