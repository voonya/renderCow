#pragma once
#include <vector>
#include "Box.h"
#include "Triangle.h"

using namespace std;

struct Node
{
	Box box;
	vector<Triangle> triangles;
	Node* ptr_node[8];
	Node(Box region, vector<Triangle> tr)
	{
		box = region;
		triangles = tr;
		for (int i = 0; i < 8; i++)
			ptr_node[i] = nullptr;
	}
	//Node();
};

class OctoTree
{
public:
	int count_tr = 10;
	float min_size = 0.001;
	Node* root;
	OctoTree(Box box, vector<Triangle> tr);
	void divCube(Node*& root);
	bool isTriangleIn(Triangle f, Box box);
};