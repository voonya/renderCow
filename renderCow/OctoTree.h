#pragma once
#include <vector>
#include "Box.h"
#include "Triangle.h"
using namespace std;
class OctoTree
{
	Node* root;
public:
	OctoTree();
};

struct Node
{
	int count_tr = 10;
	float min_size = 0.001;
	Box box;
	vector<Triangle> triangles;
	Node* ptr_node[8];
	Node(Box region, vector<Triangle> tr) { box = region; triangles = tr;}
	Node();
};