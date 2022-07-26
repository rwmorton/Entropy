//local dependencies
#include <entropy\math\r3\line3.h>

namespace entropy
{

Line3::Line3(const Point3 &p1,const Point3 &p2)
{
	p = p1;
	d = p2 - p1;
	d.normalize();
}

Line3::Line3(const Point3 &p,const Vector3 &d)
{
	this->p = p;
	this->d = d;
}

Line3::Line3(const Line3 &right)
{
	p = right.p;
	d = right.d;
}

Line3 &Line3::operator=(const Line3 &l)
{
	p = l.p;
	d = l.d;
	return *this;
}

Point3 Line3::operator()(float t) const
{
	return p + d * t;
}

float Line3::distance(const Point3 &p) const
{
	return (p - this->p).perpendicularTo(d).length();
}

}
