//local dependencies
#include <entropy\math\r3\normal3.h>
#include <entropy\math\r3\vector3.h>
#include <entropy\math\math.h>

namespace entropy
{

//static variable definitions
const Normal3 Normal3::ZERO(0.0f,0.0f,0.0f);
const Normal3 Normal3::X_AXIS(1.0f,0.0f,0.0f);
const Normal3 Normal3::Y_AXIS(0.0f,1.0f,0.0f);
const Normal3 Normal3::Z_AXIS(0.0f,0.0f,1.0f);

Normal3::Normal3(const Vector3 &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Normal3::Normal3(const Normal3 &right)
{
	x = right.x;
	y = right.y;
	z = right.z;
}

Normal3 &Normal3::operator=(const Normal3 &n)
{
	x = n.x;
	y = n.y;
	z = n.z;
	return *this;
}

Normal3::operator float*()
{
	return &x;
}

float &Normal3::operator[](int i)
{
	ASSERT(i >= 0 && i <= 2);
	return *((&x) + i);
}

Normal3 Normal3::operator+(const Normal3 &n) const
{
	return Normal3(x+n.x,y+n.y,z+n.z);
}

Normal3 Normal3::operator+=(const Normal3 &n)
{
	x += n.x;
	y += n.y;
	z += n.z;
	return *this;
}

Normal3 Normal3::operator-() const
{
	return Normal3(-x,-y,-z);
}

Normal3 Normal3::operator-(const Normal3 &n) const
{
	return Normal3(x-n.x,y-n.y,z-n.z);
}

Normal3 Normal3::operator-=(const Normal3 &n)
{
	x -= n.x;
	y -= n.y;
	z -= n.z;
	return *this;
}

Normal3 Normal3::operator*(float scalar) const
{
	return Normal3(x*scalar,y*scalar,z*scalar);
}

Normal3 &Normal3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Normal3 Normal3::operator/(float scalar) const
{
	float i = Math::inverse(scalar);
	return Normal3(x*i,y*i,z*i);
}

Normal3 &Normal3::operator/=(float scalar)
{
	float i = Math::inverse(scalar);
	x *= i;
	y *= i;
	z *= i;
	return *this;
}

bool Normal3::operator==(const Normal3 &n) const
{
	return x == n.x && y == n.y && z == n.z;
}

bool Normal3::operator!=(const Normal3 &n) const
{
	return x != n.x || y != n.y || z != n.z;
}

//stream output
std::ostream &operator<<(std::ostream &out,const Normal3 &n)
{
	out << n.x << ',' << n.y << ',' << n.z;
	return out;
}

float Normal3::dot(const Normal3 &n) const { return x*n.x + y*n.y + z*n.z; }

float Normal3::dot(const Vector3 &v) const { return x*v.x + y*v.y + z*v.z; }

Normal3 Normal3::cross(const Normal3 &n) const
{
	return Normal3
	(
		y*n.z - z*n.y,
		z*n.x - x*n.z,
		x*n.y - y*n.x
	);
}

Normal3 Normal3::cross(const Vector3 &v) const
{
	return Normal3
	(
		y*v.z - z*v.y,
		z*v.x - x*v.z,
		x*v.y - y*v.x
	);
}

float Normal3::length() const { return Math::sqrt(x*x + y*y + z*z); }

float Normal3::lengthSquared() const { return x*x + y*y + z*z; }

void Normal3::normalize()
{
	float invLength = Math::inverse(length());
	x *= invLength;
	y *= invLength;
	z *= invLength;
}

//perpendicular projection of this onto n
Normal3 Normal3::perpendicularTo(const Normal3 &n) const
{
	return (*this) - n * ((x*n.x + y*n.y + z*n.z)/(n.x*n.x + n.y*n.y + n.z*n.z));
}

//parallel projection of this onto n
Normal3 Normal3::parallelTo(const Normal3 &n) const
{
	return n * ((x*n.x + y*n.y + z*n.z)/(n.x*n.x + n.y*n.y + n.z*n.z));
}

//test
#ifdef DEBUG
void Normal3::test()
{
	std::cout << "Normal3 tests" << std::endl;
	//std::cout << "Normal3::dot((1,0),(0,1)) -> should return 0: " << Normal3::X_AXIS.dot(Normal3::Y_AXIS) << std::endl;
	//std::cout << "Normal3::length(1,1) -> should return 1.414: " << Normal3(1,1).length() << std::endl;
	//std::cout << "Normal3::lengthSquared(1,1) -> should return 2: " << std::endl;
	//std::cout << "parallel projection of (1,1) onto (2,0) -> should return (1,0): " << Normal3(1,1).parallelTo(Normal3(2,0)) << std::endl;
	//std::cout << "perpendicular projection of (1,1) onto (2,0) -> should return (0,1): " << Normal3(1,1).perpendicularTo(Normal3(2,0)) << std::endl;
	//Normal3 n(2,2);
	//std::cout << "before normalizing: " << n << std::endl;
	//n.normalize();
	//std::cout << "after normalizing: " << n << std::endl;
	std::cout << std::endl;
}
#endif

}
