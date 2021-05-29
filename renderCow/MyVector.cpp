#include "MyVector.h"
#include <Math.h>

MyVector MyVector::getOrt()
{
	MyVector ort;
	double mod = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	ort.x = x / mod;
	ort.y = y / mod;
	ort.z = z / mod;
	return ort;
}

MyVector MyVector::cross(MyVector vec1, MyVector vec2)
{
	MyVector vec3;
	vec3.x = vec1.y * vec2.z - vec1.z * vec2.y;
	vec3.y = vec1.z * vec2.x - vec1.x * vec2.z;
	vec3.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return vec3;
}

double MyVector::dot(MyVector vec1, MyVector vec2)
{
	double res;
	res = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return res;
}

MyVector MyVector::operator*(const double a)
{
	MyVector vec;
	vec.x = a * x;
	vec.y = a * y;
	vec.z = a * z;

	return vec;
}

Point MyVector::operator+(const Point point)
{
	Point point1;
	point1.x = x + point.x;
	point1.y = y + point.y;
	point1.z = z + point.z;
	return point1;
}

MyVector MyVector::operator+(const MyVector vec1)
{
	MyVector vec3;
	vec3.x = x + vec1.x;
	vec3.y = y + vec1.y;
	vec3.z = z + vec1.z;
	return vec3;
}

MyVector MyVector::operator-(const MyVector vec1)
{
	MyVector vec3;
	vec3.x = x - vec1.x;
	vec3.y = y - vec1.y;
	vec3.z = z - vec1.z;
	return vec3;
}