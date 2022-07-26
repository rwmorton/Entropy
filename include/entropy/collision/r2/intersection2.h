#ifndef __intersection2_h__
#define __intersection2_h__

//local dependencies
#include <entropy\math\r2\point2.h>
#include <entropy\math\r2\vector2.h>
#include <entropy\math\r2\normal2.h>

namespace entropy
{

//holds 2 dimensional intersection information
struct Intersection2
{
	//variables
	Point2 p;		//intersected point
	Normal2 nn;		//normalized normal normal at point
	Vector2 t;		//tangent to normal at point
};

}

#endif
