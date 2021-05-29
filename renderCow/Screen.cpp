#include "Screen.h"
#include <iostream>

Screen::Screen(MyVector dir, Point camera, double dist1)
{
	height = 100;
	width = 100;
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
	corner = center + right * (width / 2);
	corner = corner + up * (-height / 2);
	points = new Point * [height];
	for (int i = 0; i < height; i++)
	{
		points[i] = new Point[width];
	}
	points[0][0] = corner;
	for (int i = 0; i < height; i++)
	{
		if (i != 0)
			points[i][0] = points[i - 1][0] + up;
		for (int j = 1; j < width; j++)
		{
			points[i][j] = points[i][j - 1] + right;
		}
	}
}

double triangle_intersection(Point point, Point camera, Triangle triangle) 
{
	MyVector orig(point);
	MyVector dir(point, camera);
	MyVector v0(triangle.v1);
	MyVector v1(triangle.v2);
	MyVector v2(triangle.v3);

	MyVector e1 = v1 - v0;
	MyVector e2 = v2 - v0;
	// Вычисление вектора нормали к плоскости
	MyVector pvec = MyVector::cross(dir, e2);
	float det = dot(e1, pvec);

	// Луч параллелен плоскости
	if (det < 1e-8 && det > -1e-8) {
		return 0;
	}

	float inv_det = 1 / det;
	MyVector tvec = orig - v0;
	float u = dot(tvec, pvec) * inv_det;
	if (u < 0 || u > 1) {
		return 0;
	}

	MyVector qvec = MyVector::cross(tvec, e1);
	float v = dot(dir, qvec) * inv_det;
	if (v < 0 || u + v > 1) {
		return 0;
	}
	return dot(e2, qvec) * inv_det;
}