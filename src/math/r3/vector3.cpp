//local dependencies
#include <entropy\math\r3\vector3.h>
#include <entropy\math\r3\point3.h>
#include <entropy\math\r3\normal3.h>
#include <entropy\math\math.h>

namespace entropy
{

//static variable definitions
const Vector3 Vector3::ZERO(0.0f,0.0f,0.0f);
const Vector3 Vector3::X_AXIS(1.0f,0.0f,0.0f);
const Vector3 Vector3::Y_AXIS(0.0f,1.0f,0.0f);
const Vector3 Vector3::Z_AXIS(0.0f,0.0f,1.0f);

Vector3::Vector3(const Point3 &p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}

Vector3::Vector3(const Normal3 &n)
{
	x = n.x;
	y = n.y;
	z = n.z;
}

Vector3::Vector3(const Vector3 &right)
{
	x = right.x;
	y = right.y;
	z = right.z;
}

Vector3 &Vector3::operator=(const Vector3 &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector3::operator float*()
{
	return &x;
}

float &Vector3::operator[](int i)
{
	ASSERT(i >= 0 && i <= 2);
	return *((&x) + i);
}

Vector3 Vector3::operator+(const Vector3 &v) const
{
	return Vector3(x+v.x,y+v.y,z+v.z);
}

Vector3 Vector3::operator+=(const Vector3 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x,-y,-z);
}

Vector3 Vector3::operator-(const Vector3 &v) const
{
	return Vector3(x-v.x,y-v.y,z-v.z);
}

Vector3 Vector3::operator-=(const Vector3 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3 Vector3::operator*(float scalar) const
{
	return Vector3(x*scalar,y*scalar,z*scalar);
}

Vector3 &Vector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector3 Vector3::operator/(float scalar) const
{
	float i = Math::inverse(scalar);
	return Vector3(x*i,y*i,z*i);
}

Vector3 &Vector3::operator/=(float scalar)
{
	float i = Math::inverse(scalar);
	x *= i;
	y *= i;
	z *= i;
	return *this;
}

bool Vector3::operator==(const Vector3 &v) const
{
	return x == v.x && y == v.y && z == v.z;
}

bool Vector3::operator!=(const Vector3 &v) const
{
	return x != v.x || y != v.y || z != v.z;
}

//stream output
std::ostream &operator<<(std::ostream &out,const Vector3 &v)
{
	out << v.x << ',' << v.y << ',' << v.z;
	return out;
}

float Vector3::dot(const Vector3 &v) const { return x*v.x + y*v.y + z*v.z; }

float Vector3::dot(const Normal3 &n) const { return x*n.x + y*n.y + z*n.z; }

Vector3 Vector3::cross(const Vector3 &v) const
{
	return Vector3
	(
		y*v.z - z*v.y,
		z*v.x - x*v.z,
		x*v.y - y*v.x
	);
}

Vector3 Vector3::cross(const Normal3 &n) const
{
	return Vector3
	(
		y*n.z - z*n.y,
		z*n.x - x*n.z,
		x*n.y - y*n.x
	);
}

float Vector3::length() const { return Math::sqrt(x*x + y*y + z*z); }

float Vector3::lengthSquared() const { return x*x + y*y + z*z; }

void Vector3::normalize()
{
	float invLength = Math::inverse(length());
	x *= invLength;
	y *= invLength;
	z *= invLength;
}

//perpendicular projection of this onto v
Vector3 Vector3::perpendicularTo(const Vector3 &v) const
{
	return (*this) - v * ((x*v.x + y*v.y + z*v.z)/(v.x*v.x + v.y*v.y + v.z*v.z));
}

//parallel projection of this onto v
Vector3 Vector3::parallelTo(const Vector3 &v) const
{
	return v * ((x*v.x + y*v.y + z*v.z)/(v.x*v.x + v.y*v.y + v.z*v.z));
}

//test
#ifdef DEBUG
void Vector3::test()
{
	std::cout << "Vector3 tests" << std::endl;
	//std::cout << "Vector3::dot((1,0),(0,1)) -> should return 0: " << Vector3::X_AXIS.dot(Vector3::Y_AXIS) << std::endl;
	//std::cout << "Vector3::length(1,1) -> should return 1.414: " << Vector3(1,1).length() << std::endl;
	//std::cout << "Vector3::lengthSquared(1,1) -> should return 2: " << std::endl;
	//std::cout << "parallel projection of (1,1) onto (2,0) -> should return (1,0): " << Vector3(1,1).parallelTo(Vector3(2,0)) << std::endl;
	//std::cout << "perpendicular projection of (1,1) onto (2,0) -> should return (0,1): " << Vector3(1,1).perpendicularTo(Vector3(2,0)) << std::endl;
	//Vector3 v(2,2);
	//std::cout << "before normalizing: " << v << std::endl;
	//v.normalize();
	//std::cout << "after normalizing: " << v << std::endl;
	std::cout << std::endl;
}
#endif

}
