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
	std::vector<Triangle> parseFile(std::string path, std::vector<Point>& points);
	Point parseLine(std::string line);
	Triangle parseLine(std::string line, std::vector<Point> points);
	std::string getPath(std::string filename);
};

