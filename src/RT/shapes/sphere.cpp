//local dependencies
#include <entropy\RT\shapes\sphere.h>
#include <entropy\math\math.h>

namespace entropy
{

Sphere::Sphere(const Transform3 &l2w,bool reverseOrientation,float radius) : Shape(l2w,reverseOrientation),radius(Math::abs(radius)) {}

BBox3 Sphere::localBound() const
{
	return BBox3
	(
		Point3(-radius,-radius,-radius),
		Point3(radius,radius,radius)
	);
}

bool Sphere::canIntersect() const
{
	return true;
}

bool Sphere::intersect(const Ray3 &ray,float *tHit,DG &dg) const
{
	Ray3 r = WorldToLocal(ray); //transform ray to local space

	//quadratic coefficients
	float A = r.d.x*r.d.x + r.d.y*r.d.y + r.d.z*r.d.z;
	float B = 2.0f * (r.o.x*r.d.x + r.o.y*r.d.y + r.o.z*r.d.z);
	float C = r.o.x*r.o.x + r.o.y*r.o.y + r.o.z*r.o.z - radius*radius;

	//compute roots
	float t0,t1;
	if(Math::quadratic(A,B,C,&t0,&t1) == Math::NO_ROOTS)
	{
		return false;
	}

	//get root
	if(t0 > r.maxt || t1 < r.mint)
	{
		return false;
	}
	*tHit = t0;
	if(t0 < r.mint)
	{
		if(t1 > r.maxt)
		{
			return false;
		}
		*tHit = t1;
	}

	//fill in differential geometry
	//explicit construct for now, as havent
	//computed the surface derivatives
	dg.p = LocalToWorld(r(*tHit));
	Vector3 cp = r(*tHit) - Point3::ZERO;
	dg.nn = Normal3(cp.x,cp.y,cp.z);
	dg.nn.normalize();
	dg.shape = this;
	//
	//dg.p = DG( ... );
	//
	//TODO the rest of it

	return true;
}

bool Sphere::intersectP(const Ray3 &ray) const
{
	Ray3 r = WorldToLocal(ray); //transform ray to local space

	//quadratic coefficients
	float A = r.d.x*r.d.x + r.d.y*r.d.y + r.d.z*r.d.z;
	float B = 2.0f * (r.o.x*r.d.x + r.o.y*r.d.y + r.o.z*r.d.z);
	float C = r.o.x*r.o.x + r.o.y*r.o.y + r.o.z*r.o.z - radius*radius;

	//compute roots
	float t0,t1;
	if(Math::quadratic(A,B,C,&t0,&t1) == Math::NO_ROOTS)
	{
		return false;
	}

	return true;
}

float Sphere::area() const
{
	return 4.0f * Math::PI * radius * radius; //4 Pi r^2
}

void Sphere::debug() const
{
	glPushMatrix();
	glMultMatrixf(LocalToWorld.transpose());

	glutWireSphere(radius,32,32);

	glPopMatrix();
}

}
