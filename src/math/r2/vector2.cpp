//local dependencies
#include <entropy\math\r2\vector2.h>
#include <entropy\math\r2\point2.h>
#include <entropy\math\r2\normal2.h>
#include <entropy\math\math.h>

namespace entropy
{

//static variable definitions
const Vector2 Vector2::ZERO(0.0f,0.0f);
const Vector2 Vector2::X_AXIS(1.0f,0.0f);
const Vector2 Vector2::Y_AXIS(0.0f,1.0f);

Vector2::Vector2(const Point2 &p)
{
	x = p.x;
	y = p.y;
}

Vector2::Vector2(const Normal2 &n)
{
	x = n.x;
	y = n.y;
}

Vector2::Vector2(const Vector2 &right)
{
	x = right.x;
	y = right.y;
}

Vector2 &Vector2::operator=(const Vector2 &v)
{
	x = v.x;
	y = v.y;
	return *this;
}

Vector2::operator float*()
{
	return &x;
}

float &Vector2::operator[](int i)
{
	ASSERT(i >= 0 && i <= 1);
	return *((&x) + i);
}

Vector2 Vector2::operator+(const Vector2 &v) const
{
	return Vector2(x+v.x,y+v.y);
}

Vector2 Vector2::operator+=(const Vector2 &v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x,-y);
}

Vector2 Vector2::operator-(const Vector2 &v) const
{
	return Vector2(x-v.x,y-v.y);
}

Vector2 Vector2::operator-=(const Vector2 &v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(x*scalar,y*scalar);
}

Vector2 &Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2 Vector2::operator/(float scalar) const
{
	float i = Math::inverse(scalar);
	return Vector2(x*i,y*i);
}

Vector2 &Vector2::operator/=(float scalar)
{
	float i = Math::inverse(scalar);
	x *= i;
	y *= i;
	return *this;
}

bool Vector2::operator==(const Vector2 &v) const
{
	return x == v.x && y == v.y;
}

bool Vector2::operator!=(const Vector2 &v) const
{
	return x != v.x || y != v.y;
}

//stream output
std::ostream &operator<<(std::ostream &out,const Vector2 &v)
{
	out << v.x << ',' << v.y;
	return out;
}

float Vector2::dot(const Vector2 &v) const { return x*v.x + y*v.y; }

float Vector2::dot(const Normal2 &n) const { return x*n.x + y*n.y; }

float Vector2::length() const { return Math::sqrt(x*x + y*y); }

float Vector2::lengthSquared() const { return x*x + y*y; }

void Vector2::normalize()
{
	float invLength = Math::inverse(length());
	x *= invLength;
	y *= invLength;
}

Vector2 Vector2::perpendicular() const
{
	return Vector2(-y,x);
}

//perpendicular projection of this onto v
Vector2 Vector2::perpendicularTo(const Vector2 &v) const
{
	return (*this) - v * ((x*v.x + y*v.y)/(v.x*v.x + v.y*v.y));
}

//parallel projection of this onto v
Vector2 Vector2::parallelTo(const Vector2 &v) const
{
	return v * ((x*v.x + y*v.y)/(v.x*v.x + v.y*v.y));
}

//test
#ifdef DEBUG
void Vector2::test()
{
	std::cout << "Vector2 tests" << std::endl;
	std::cout << "Vector2::dot((1,0),(0,1)) -> should return 0: " << Vector2::X_AXIS.dot(Vector2::Y_AXIS) << std::endl;
	std::cout << "Vector2::length(1,1) -> should return 1.414: " << Vector2(1,1).length() << std::endl;
	std::cout << "Vector2::lengthSquared(1,1) -> should return 2: " << std::endl;
	//std::cout << "parallel projection of (1,1) onto (2,0) -> should return (1,0): " << Vector2(1,1).parallelTo(Vector2(2,0)) << std::endl;
	//std::cout << "perpendicular projection of (1,1) onto (2,0) -> should return (0,1): " << Vector2(1,1).perpendicularTo(Vector2(2,0)) << std::endl;
	Vector2 v(2,2);
	std::cout << "before normalizing: " << v << std::endl;
	v.normalize();
	std::cout << "after normalizing: " << v << std::endl;
	std::cout << std::endl;
}
#endif

}
