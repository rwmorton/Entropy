#ifndef __sphere_h__
#define __sphere_h__

//local dependencies
#include <entropy\RT\core\shape.h>

namespace entropy
{

class Sphere : public Shape
{
public:
	//constructor
	Sphere(const Transform3 &l2w,bool reverseOrientation,float radius);
	//methods
	virtual BBox3 localBound() const;
	virtual bool canIntersect() const;
	virtual bool intersect(const Ray3 &ray,float *tHit,DG &dg) const;
	virtual bool intersectP(const Ray3 &ray) const;
	virtual float area() const;
	virtual void debug() const;
private:
	//variables
	float radius;
protected:
	//
};

}

#endif
