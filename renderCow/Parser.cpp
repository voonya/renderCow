#include "Parser.h"
#include <iostream>
std::vector<Triangle> Parser::parseFile(std::string filename)
{
    std::vector<Triangle> triangles;
    std::vector<Point> points;
    std::ifstream file(getPath(filename));
    std::string line;
    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, line);
            if (line[0] == 'v' && line[1] == ' ') {
                Point p = parseLine(line);
                points.push_back(p);
            }
            else if (line[0] == 'f' && line[1] == ' ') {
                Triangle tr = parseLine(line, points);
                triangles.push_back(tr);
            }
        }
    }
    else {
        std::cout << "Cant read the file\n";
    }


    return triangles;
}

Point Parser::parseLine(std::string line)
{
    std::string lineCopy = line;

    lineCopy.erase(0, 2);
    double x = stod(lineCopy.substr(0, lineCopy.find(" ")));

    lineCopy.erase(0, lineCopy.find(" ") + 1);
    double y = stod(lineCopy.substr(0, lineCopy.find(" ")));

    lineCopy.erase(0, lineCopy.find(" ") + 1);
    double z = stod(lineCopy);

    return Point(x, y, z);
}

Triangle Parser::parseLine(std::string line, std::vector<Point> points)
{
    std::string lineCopy = line;

    lineCopy.erase(0, 2);
    std::string pointStr = lineCopy.substr(0, line.find(" "));
    pointStr = pointStr.substr(0, pointStr.find("/"));
    int p1 = stoi(pointStr);

    lineCopy.erase(0, lineCopy.find(" ") + 1);
    pointStr = lineCopy.substr(0, line.find(" "));
    pointStr = pointStr.substr(0, pointStr.find("/"));
    int p2 = stoi(pointStr);

    lineCopy.erase(0, lineCopy.find(" ") + 1);
    pointStr = lineCopy.substr(0, line.find(" "));
    pointStr = pointStr.substr(0, pointStr.find("/"));
    
    int p3 = stoi(pointStr);
    return Triangle(points[p1-1], points[p2-1], points[p3-1]);
}

std::string Parser::getPath(std::string filename)
{
    return std::filesystem::current_path().string() + "/" + filename;
}
