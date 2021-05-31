#include "OctoTree.h"
#include <iostream>

OctoTree::OctoTree(Box box, vector<Triangle> tr)
{
	root = new Node(box, tr);
    divCube(root); 
}

void OctoTree::divCube(Node*& root)
{
	Point center;
	center.x = (root->box.max.x + root->box.min.x) / 2;
	center.y = (root->box.max.y + root->box.min.y) / 2;
	center.z = (root->box.max.z + root->box.min.z) / 2;
    vector<Box> boxes;
	boxes.push_back(Box(center, root->box.max));

    boxes.push_back(Box(center, root->box.min));

	Point point3(root->box.min.x, center.y, root->box.min.z);
    Point point33(center.x, root->box.max.y, center.z);
    boxes.push_back(Box(point3, point33));

	Point point4(root->box.max.x, root->box.max.y, center.z);
    Point point44(center.x, center.y, root->box.min.z);
    boxes.push_back(Box(point4, point44));


	Point point5(center.x, root->box.min.y, root->box.min.z);
    Point point55(root->box.max.x, center.y, center.z);
    boxes.push_back(Box(point55, point5));


	Point point6(center.x, root->box.min.y, center.z);
    Point point66(root->box.max.x, center.y, root->box.max.z);
    boxes.push_back(Box(point66, point6));


	Point point7(root->box.min.x, root->box.min.y, center.z);
    Point point77(center.x, center.y, root->box.max.z);
    boxes.push_back(Box(point77, point7));


	Point point8(root->box.min.x, center.y, center.z);
    Point point88(center.x, root->box.max.y, root->box.max.z);
    boxes.push_back(Box(point88, point8));

    

    for (int j = 0; j < boxes.size(); j++)
    {
        vector<Triangle> tr1;
        for (int i = 0; i < root->triangles.size(); i++)
        {
            if (isTriangleIn(root->triangles[i], boxes[j]))
                tr1.push_back(root->triangles[i]);
        }
        root->ptr_node[j] = new Node(boxes[j], tr1);
    }

    for (int i = 0; i < 8; i++)
    {
        if ((root->ptr_node[i]->triangles.size() > 10) && (root->ptr_node[i]->box.max.x - root->ptr_node[i]->box.min.x > 0.0001))
            divCube(root->ptr_node[i]);
    } 
}

//

bool OctoTree::isTriangleIn(Triangle f, Box box)
{
    MyVector c = (MyVector(box.min) + MyVector(box.max)) * 0.5;
    float e0 = (box.max.x - box.min.x) * 0.5;
    float e1 = (box.max.y - box.min.y) * 0.5;
    float e2 = (box.max.z - box.min.z) * 0.5;

    MyVector v0 = MyVector(f.v1) - c;
    MyVector v1 = MyVector(f.v2) - c;
    MyVector v2 = MyVector(f.v3) - c;

    MyVector f0 = MyVector(f.v2) - MyVector(f.v1);
    MyVector f1 = MyVector(f.v3) - MyVector(f.v2);
    MyVector f2 = MyVector(f.v1) - MyVector(f.v3);

    MyVector a00;
    a00.x = 0;
    a00.y = -f0.z;
    a00.z = f0.y;

    float p0 = MyVector::dot(v0, a00);
    float p1 = MyVector::dot(v1, a00);
    float p2 = MyVector::dot(v2, a00);
    float r = e1 * abs(f0.z) + e2 * abs(f0.y);
    if (max(-max(p2, max(p0, p1)), min(min(p0, p1), p2)) > r)
    {
        
        return false;
    }

    MyVector a01;
    a01.x = 0;
    a01.y = -f1.z;
    a01.z = f1.y;

    p0 = MyVector::dot(v0, a01);
    p1 = MyVector::dot(v1, a01);
    p2 = MyVector::dot(v2, a01);
    r = e1 * abs(f1.z) + e2 * abs(f1.y);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r)
    {
        return false;
    }


    MyVector a02;
    a02.x = 0;
    a02.y = -f2.z;
    a02.z = f2.y;

    p0 = MyVector::dot(v0, a02);
    p1 = MyVector::dot(v1, a02);
    p2 = MyVector::dot(v2, a02);
    r = e1 * abs(f2.z) + e2 * abs(f2.y);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r)
    {
        return false;
    }

    MyVector a10;
    a10.x = f0.z;
    a10.y = 0;
    a10.z = -f0.x;

    p0 = MyVector::dot(v0, a10);
    p1 = MyVector::dot(v1, a10);
    p2 = MyVector::dot(v2, a10);
    r = e0 * abs(f0.z) + e2 * abs(f0.x);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r)
    {
        return false;
    }

    MyVector a11;
    a11.x = f1.z;
    a11.y = 0;
    a11.z = -f1.x;

    p0 = MyVector::dot(v0, a11);
    p1 = MyVector::dot(v1, a11);
    p2 = MyVector::dot(v2, a11);
    r = e0 * abs(f1.z) + e2 * abs(f1.x);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r)
    {
        return false;
    }

    MyVector a12;
    a12.x = f2.z;
    a12.y = 0;
    a12.z = -f2.x;

    p0 = MyVector::dot(v0, a12);
    p1 = MyVector::dot(v1, a12);
    p2 = MyVector::dot(v2, a12);
    r = e0 * abs(f2.z) + e2 * abs(f2.x);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r)
    {
        return false;
    }

    MyVector a20;
    a20.x = -f0.y;
    a20.y = f0.x;
    a20.z = 0;

    p0 = MyVector::dot(v0, a20);
    p1 = MyVector::dot(v1, a20);
    p2 = MyVector::dot(v2, a20);
    r = e0 * abs(f0.y) + e1 * abs(f0.x);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r)
    {
        return false;
    }

    MyVector a21;
    a21.x = -f1.y;
    a21.y = f1.x;
    a21.z = 0;

    p0 = MyVector::dot(v0, a21);
    p1 = MyVector::dot(v1, a21);
    p2 = MyVector::dot(v2, a21);
    r = e0 * abs(f1.y) + e1 * abs(f1.x);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r)
    {
        return false;
    }

    MyVector a22;
    a22.x = -f2.y;
    a22.y = f2.x;
    a22.z = 0;

    p0 = MyVector::dot(v0, a22);
    p1 = MyVector::dot(v1, a22);
    p2 = MyVector::dot(v2, a22);
    r = e0 * abs(f2.y) + e1 * abs(f2.x);
    if (max(-max(p0, max(p1, p2)), min(min(p0, p1), p2)) > r)
    {
        return false;
    }


    if (max(v0.x, max(v1.x, v2.x)) < -e0 || min(v0.x, min(v1.x, v2.x)) > e0)
    {
        return false;
    }

    if (max(v0.y, max(v1.y, v2.y)) < -e1 || min(v0.y, min(v1.y, v2.y)) > e1)
    {
        return false;
    }

    if (max(v0.z, max(v1.z, v2.z)) < -e2 || min(v0.z, min(v1.z, v2.z)) > e2)
    {
        return false;
    }
    return true;
}

int OctoTree::IntersectRayAABB(Point p, MyVector vec, Box a, float& t)
{
    MyVector dirfrac;
    dirfrac.x = 1.0f / vec.x;
    dirfrac.y = 1.0f / vec.y;
    dirfrac.z = 1.0f / vec.z;
    // lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
    // r.org is origin of ray
    float t1 = (a.min.x - p.x) * dirfrac.x;
    float t2 = (a.max.x - p.x) * dirfrac.x;
    float t3 = (a.min.y - p.y) * dirfrac.y;
    float t4 = (a.max.y - p.y) * dirfrac.y;
    float t5 = (a.min.z - p.z) * dirfrac.z;
    float t6 = (a.max.z - p.z) * dirfrac.z;

    float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
    float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

    // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
    if (tmax < 0)
    {
        t = tmax;
        return false;
    }

    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
    {
        t = tmax;
        return false;
    }

    t = tmin;
    return true;
}