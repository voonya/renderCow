#include "Triangle.h"

bool Triangle::isEqual(Triangle tr)
{
	if (v1.isEqual(tr.v1) && v2.isEqual(tr.v2) && v3.isEqual(tr.v3))
		return true;
	else
		return false;
}
