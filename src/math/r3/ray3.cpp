//local dependencies
#include <entropy\math\r3\ray3.h>
#include <entropy\math\math.h>

namespace entropy
{

Ray3::Ray3() : mint(Math::EPSILON),maxt(Math::MAX),tHit(0.0f) {}

Ray3::Ray3(const Point3 &origin,const Vector3 &direction) : mint(Math::RAY_EPSILON),maxt(Math::MAX),tHit(0.0f)
{
	o = origin;
	d = direction;
	d.normalize();
}

Ray3::Ray3(const Ray3 &right)
{
	o = right.o;
	d = right.d;
	mint = right.mint;
	maxt = right.maxt;
	tHit = right.tHit;
}

Ray3 &Ray3::operator=(const Ray3 &r)
{
	o = r.o;
	d = r.d;
	mint = r.mint;
	maxt = r.maxt;
	tHit = r.tHit;
	return *this;
}

Point3 Ray3::operator()(float t) const
{
	return o + (d * t);
}

std::ostream &operator<<(std::ostream &out,const Ray3 &r)
{
	out << r.o << ' ' << r.d << ' ' << r.tHit;
	return out;
}

Point3 Ray3::getOrigin() const
{
	return o;
}

void Ray3::setOrigin(const Point3 &origin)
{
	o = origin;
}

Vector3 Ray3::getDirection() const
{
	return d;
}

void Ray3::setDirection(const Vector3 &direction)
{
	d = direction;
	d.normalize();
}

}
