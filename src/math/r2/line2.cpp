//local dependencies
#include <entropy\math\r2\line2.h>

namespace entropy
{

Line2::Line2(const Point2 &p1,const Point2 &p2)
{
	p = p1;
	d = p2 - p1;
	d.normalize();
}

Line2::Line2(const Point2 &p,const Vector2 &d)
{
	this->p = p;
	this->d = d;
}

Line2::Line2(const Line2 &right)
{
	p = right.p;
	d = right.d;
}

Line2 &Line2::operator=(const Line2 &l)
{
	p = l.p;
	d = l.d;
	return *this;
}

Point2 Line2::operator()(float t) const
{
	return p + d * t;
}

float Line2::distance(const Point2 &p) const
{
	return (p - this->p).perpendicularTo(d).length();
}

}
