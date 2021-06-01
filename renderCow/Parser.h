#pragma once
#include "Triangle.h"
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
class Parser
{
public:
	Parser() {};
	vector<Triangle> parseFile(string path, vector<Point>& points);
	Point parseLine(string line);
	Triangle parseLine(string line, vector<Point> points);
	string getPath(string filename);
};

