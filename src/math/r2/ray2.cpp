//local dependencies
#include <entropy\math\r2\ray2.h>
#include <entropy\math\math.h>

namespace entropy
{

Ray2::Ray2() : mint(Math::EPSILON),maxt(Math::MAX),tHit(0.0f) {}

Ray2::Ray2(const Point2 &origin,const Vector2 &direction) : mint(Math::EPSILON),maxt(Math::MAX),tHit(0.0f)
{
	o = origin;
	d = direction;
	d.normalize();
}

Ray2::Ray2(const Ray2 &right)
{
	o = right.o;
	d = right.d;
	mint = right.mint;
	maxt = right.maxt;
	tHit = right.tHit;
}

Ray2 &Ray2::operator=(const Ray2 &r)
{
	o = r.o;
	d = r.d;
	mint = r.mint;
	maxt = r.maxt;
	tHit = r.tHit;
	return *this;
}

Point2 Ray2::operator()(float t) const
{
	return o + (d * t);
}

std::ostream &operator<<(std::ostream &out,const Ray2 &r)
{
	out << r.o << ' ' << r.d << ' ' << r.tHit;
	return out;
}

Point2 Ray2::getOrigin() const
{
	return o;
}

void Ray2::setOrigin(const Point2 &origin)
{
	o = origin;
}

Vector2 Ray2::getDirection() const
{
	return d;
}

void Ray2::setDirection(const Vector2 &direction)
{
	d = direction;
	d.normalize();
}

}
