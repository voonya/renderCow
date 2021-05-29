#include "Screen.h"
#include <iostream>

Screen::Screen(MyVector dir, Point camera, double dist1)
{
	height = 10;
	width = 10;
	pixels = 100;
	double resolution = height / pixels;
	dist = dist1;
	MyVector n = dir.getOrt();
	a = n.x;
	b = n.y;
	c = n.z;
	d = dist;
	double t;
	t = -(a * dir.x + b * dir.y + c * dir.z) / (a * camera.x + b * camera.y + c * camera.z + d);
	center.x = camera.x + dir.x * t;
	center.y = camera.y + dir.y * t;
	center.z = camera.z + dir.z * t;
	right = (MyVector::cross(MyVector(0, 0, 1), dir)).getOrt();
	up = (MyVector::cross(dir, right)).getOrt();
	Point corner;
	corner = right * (-width / 2) + center;
	corner = up * (-height / 2) + corner;
	points = new Point * [pixels];
	for (int i = 0; i < pixels; i++)
	{
		points[i] = new Point[pixels];
	}
	points[0][0] = corner;
	for (int i = 0; i < pixels; i++)
	{
		for (int j = 0; j < pixels; j++)
		{
			points[i][j] = up * i * resolution + (right * j * resolution + corner);
		}
	}
}


double Screen::triangle_intersection(Point point, Point camera, Triangle triangle) 
{
	MyVector orig(point);
	MyVector dir(point, camera);
	MyVector v0(triangle.v1);
	MyVector v1(triangle.v2);
	MyVector v2(triangle.v3);
	//std::cout << v2.x << " " << v2.y << " " << v2.z << "\n";

	MyVector e1 = v1 - v0;
	MyVector e2 = v2 - v0;
	// Вычисление вектора нормали к плоскости
	MyVector pvec = MyVector::cross(dir, e2);
	float det = MyVector::dot(e1, pvec);

	// Луч параллелен плоскости
	if (det < 1e-8 && det > -1e-8) {
		return 0;
	}

	float inv_det = 1 / det;
	MyVector tvec = orig - v0;
	float u = MyVector::dot(tvec, pvec) * inv_det;
	if (u < 0 || u > 1) {
		return 0;
	}

	MyVector qvec = MyVector::cross(tvec, e1);
	float v = MyVector::dot(dir, qvec) * inv_det;
	if (v < 0 || u + v > 1) {
		return 0;
	}
	return MyVector::dot(e2, qvec) * inv_det;
}