//local dependencies
#include <entropy\math\r3\point3.h>
#include <entropy\math\r3\vector3.h>
#include <entropy\math\math.h>

namespace entropy
{

//static variable definitions
const Point3 Point3::ZERO(0.0f,0.0f,0.0f);
const Point3 Point3::X_AXIS(1.0f,0.0f,0.0f);
const Point3 Point3::Y_AXIS(0.0f,1.0f,0.0f);
const Point3 Point3::Z_AXIS(0.0f,0.0f,1.0f);

Point3::Point3(const Point3 &right)
{
	x = right.x;
	y = right.y;
	z = right.z;
}

Point3 &Point3::operator=(const Point3 &p)
{
	x = p.x;
	y = p.y;
	z = p.z;
	return *this;
}

Point3::operator float*()
{
	return &x;
}

float &Point3::operator[](int i)
{
	ASSERT(i >= 0 && i <= 2);
	return *((&x) + i);
}

//it doesn't make sense to add points, but a vector
//can be added to a point to give a new point
Point3 Point3::operator+(const Vector3 &v) const
{
	return Point3(x+v.x,y+v.y,z+v.z);
}

//a vector can be added to a point
Point3 Point3::operator+=(const Vector3 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

//a point subtracted from a point gives a vector
Vector3 Point3::operator-(const Point3 &p) const
{
	return Vector3(x-p.x,y-p.y,z-p.z);
}

//same as addition, except that v = (-v)
Point3 Point3::operator-(const Vector3 &v) const
{
	return Point3(x-v.x,y-v.y,z-v.z);
}

Point3 Point3::operator-=(const Vector3 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Point3 Point3::operator*(float scalar) const
{
	return Point3(x*scalar,y*scalar,z*scalar);
}

Point3 &Point3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Point3 Point3::operator/(float scalar) const
{
	float i = Math::inverse(scalar);
	return Point3(x*i,y*i,z*i);
}

Point3 &Point3::operator/=(float scalar)
{
	float i = Math::inverse(scalar);
	x *= i;
	y *= i;
	z *= i;
	return *this;
}

bool Point3::operator==(const Point3 &p) const
{
	return x == p.x && y == p.y && z == p.z;
}

bool Point3::operator!=(const Point3 &p) const
{
	return x != p.x || y != p.y || z != p.z;
}

//stream output
std::ostream &operator<<(std::ostream &out,const Point3 &p)
{
	out << p.x << ',' << p.y << ',' << p.z;
	return out;
}

float Point3::distance(const Point3 &p) const
{
	float a = x - p.x;
	float b = y - p.y;
	float c = z - p.z;
	return Math::sqrt(a*a + b*b + c*c);
}

float Point3::distanceSquared(const Point3 &p) const
{
	float a = x - p.x;
	float b = y - p.y;
	float c = z - p.z;
	return a*a + b*b + c*c;
}

//test
#ifdef DEBUG
void Point3::test()
{
	std::cout << "Point3 tests" << std::endl;
	//std::cout << "Point3::distance([0,0],[5,5]) -> should return: 7.071: " << Point3(0,0).distance(Point3(5,5)) << std::endl;
	//std::cout << "Point3::distance([-2.5,-2.5],[2.5,2.5]) -> should return: 7.071: " << Point3(-2.5f,-2.5f).distance(Point3(2.5,2.5)) << std::endl;
	//std::cout << "Point3::distanceSquared([0,0],[5,5]) -> should return: 50: " << Point3(0,0).distanceSquared(Point3(5,5)) << std::endl;
	//std::cout << "Point3::distanceSquared([-2.5,-2.5],[2.5,2.5]) -> should return: 50: " << Point3(-2.5f,-2.5f).distanceSquared(Point3(2.5,2.5)) << std::endl;
	std::cout << std::endl;
}
#endif

}
