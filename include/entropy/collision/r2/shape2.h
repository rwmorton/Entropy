#ifndef __shape2_h__
#define __shape2_h__

//local dependencies
#include <entropy\math\r2\transform2.h>
#include <entropy\math\r2\ray2.h>
#include <entropy\collision\r2\intersection2.h>

namespace entropy
{

//base class for 2 dimensional shapes
class Shape2
{
public:
	//type of shape
	enum Type
	{
		NOT_VALID,
		CIRCLE,
		BOX,
		TRIANGLE,
		CONVEX
	};
	//destructor
	~Shape2() {}
	//methods
	Shape2::Type getType() { return type; }
	virtual bool intersect(const Ray2 &ray,Intersection2 &intersection) const = 0;
private:
	//
protected:
	//constructors
	Shape2() { type = Shape2::NOT_VALID; }
	Shape2(const Transform2 &localToWorld);
	Shape2(const Shape2 &right);
	//operator overloads
	Shape2 &operator=(const Shape2 &s);
	//variables
	Type type;
	Transform2 localToWorld;
	Transform2 worldToLocal;
};

}

#endif
