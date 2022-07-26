#ifndef __intersector2_h__
#define __itersector2_h__

//local dependencies
#include <entropy\collision\r2\contact2.h>
#include <entropy\collision\r2\intersection2.h>
#include <entropy\collision\r2\collisionObject2.h>
#include <entropy\collision\r2\circle.h>
#include <entropy\math\r2\ray2.h>

namespace entropy
{

//contains methods for various intersection pairs such
//as ray/circle, ray/box2, circle/circle, box2/circle etc.
//intesectP methods are predicate methods that only take a
//shape. these are used where we don't care for anthing
//about the intersection
class Intersector2
{
public:
	//static methods

	//check for intersection between two collision objects
	static bool intersect(const CollisionObject2 &co1,const CollisionObject2 &co2,Contact2 &c);
	static bool intersectP(const CollisionObject2 &co1,const CollisionObject2 &co2);

	//ray-circle
	static bool intersect(const Ray2 &r,const Circle &c,Intersection2 &i);
	static bool intersectP(const Ray2 &r,const Circle &c);

	//ray-box2
	//ray-convex

	//circle-circle
	static bool intersect(const Circle &c1,const Circle &c2,Contact2 &c);
	static bool intersectP(const Circle &c1,const Circle &c2);

	//circle-box
private:
	//
protected:
	//
};

}

#endif
