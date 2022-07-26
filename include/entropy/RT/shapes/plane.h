#ifndef __plane_h__
#define __plane_h__

//local dependencies
#include <entropy\RT\core\shape.h>

namespace entropy
{

class Plane : public Shape
{
public:
	//constructor
	Plane(const Point3 &x,const Normal3 &n);
	//destructor
	~Plane() {}
	//methods
	virtual BBox3 localBound() const;
	virtual bool canIntersect() const;
	virtual bool intersect(const Ray3 &ray,float *tHit,DG &dg) const;
	virtual bool intersectP(const Ray3 &ray) const;
	virtual float area() const;
	virtual void debug() const;
	//variables
	Point3 x;
	Normal3 n;
private:
	//
protected:
	//
};

}

#endif
