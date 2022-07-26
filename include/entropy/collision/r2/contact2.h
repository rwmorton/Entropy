#ifndef __contact2_h__
#define __contact2_h__

//local dependencies
#include <entropy\math\r2\point2.h>
#include <entropy\math\r2\vector2.h>
#include <entropy\math\r2\normal2.h>

namespace entropy
{

//holds contact information between a pair
//of two dimensional objects
struct Contact2
{
	Point2 p;		//point
	Normal2 nn;		//normalized normal at point
	Vector2 t;		//tangent to normal at point
	float depth;	//contact penetration depth
};

}

#endif
