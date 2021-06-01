#include "Parser.h"
#include <iostream>
using namespace std;
vector<Triangle> Parser::parseFile(string filename, vector<Point>& p)
{
    vector<Triangle> triangles;
    vector<Point> points;
    ifstream file(getPath(filename));
    string line;
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
        cout << "Cant read the file\n";
    }
    p = points;

    return triangles;
}

Point Parser::parseLine(string line)
{
    string lineCopy = line;

    lineCopy.erase(0, 2);
    double x = stod(lineCopy.substr(0, lineCopy.find(" ")));

    lineCopy.erase(0, lineCopy.find(" ") + 1);
    double y = stod(lineCopy.substr(0, lineCopy.find(" ")));

    lineCopy.erase(0, lineCopy.find(" ") + 1);
    double z = stod(lineCopy);
    return Point(x, y, z);
}

Triangle Parser::parseLine(string line,vector<Point> points)
{
    string lineCopy = line;

    lineCopy.erase(0, 2);
    int p1 = stoi(lineCopy.substr(0, lineCopy.find("/")));
    lineCopy.erase(0, lineCopy.find(" ") + 1);
    int p2 = stoi(lineCopy.substr(0, lineCopy.find("/")));
    lineCopy.erase(0, lineCopy.find(" ") + 1);
    int p3 = stoi(lineCopy);
    return Triangle(points[p1-1], points[p2-1], points[p3-1]);
}

string Parser::getPath(string filename)
{
    return filesystem::current_path().string() + "/" + filename;
}
