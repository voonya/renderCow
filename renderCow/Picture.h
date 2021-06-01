#pragma once
#include <fstream>
#include <cstdlib>
#include "BMPstruct.h"
using namespace std;
class Picture
{
	BMP_head head;
	Pixel_triplet** pixels;
public:
	void reflection_horizontal();
	void reflectionVertical();
	void write_picture(string, double**, int, int);
};

