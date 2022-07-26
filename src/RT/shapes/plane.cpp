//local dependencies
#include <entropy\RT\shapes\plane.h>
#include <entropy\math\math.h>

namespace entropy
{

Plane::Plane(const Point3 &x,const Normal3 &n) : Shape(Transform3::IDENTITY,false),x(x),n(n) {}

//assume is has infinite bound
BBox3 Plane::localBound() const
{
	return BBox3
	(
		Point3(Math::MIN,Math::MIN,Math::MIN),
		Point3(Math::MAX,Math::MAX,Math::MAX)
	);
}

bool Plane::canIntersect() const
{
	return true;
}

bool Plane::intersect(const Ray3 &ray,float *tHit,DG &dg) const
{
	//t = - (n . (ray.o - x) / (n . ray.d)

	//TODO
	return false;
}

bool Plane::intersectP(const Ray3 &ray) const
{
	//TODO
	return false;
}

float Plane::area() const
{
	return Math::MAX; //has infinite area
}

void Plane::debug() const
{
}

}
