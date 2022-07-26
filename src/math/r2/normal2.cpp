//local dependencies	
#include <entropy\math\r2\normal2.h>
#include <entropy\math\r2\vector2.h>
#include <entropy\math\math.h>

namespace entropy
{

//static variable definitions
const Normal2 Normal2::ZERO(0.0f,0.0f);
const Normal2 Normal2::X_AXIS(1.0f,0.0f);
const Normal2 Normal2::Y_AXIS(0.0f,1.0f);

Normal2::Normal2(const Vector2 &v)
{
	x = v.x;
	y = v.y;
}

Normal2::Normal2(const Normal2 &right)
{
	x = right.x;
	y = right.y;
}

Normal2 &Normal2::operator=(const Normal2 &n)
{
	x = n.x;
	y = n.y;
	return *this;
}

Normal2::operator float*()
{
	return &x;
}

float &Normal2::operator[](int i)
{
	ASSERT(i >= 0 && i <= 1);
	return *((&x) + i);
}

Normal2 Normal2::operator+(const Normal2 &n) const
{
	return Normal2(x+n.x,y+n.y);
}

Normal2 Normal2::operator+=(const Normal2 &n)
{
	x += n.x;
	y += n.y;
	return *this;
}

Normal2 Normal2::operator-() const
{
	return Normal2(-x,-y);
}

Normal2 Normal2::operator-(const Normal2 &n) const
{
	return Normal2(x-n.x,y-n.y);
}

Normal2 Normal2::operator-=(const Normal2 &n)
{
	x -= n.x;
	y -= n.y;
	return *this;
}

Normal2 Normal2::operator*(float scalar) const
{
	return Normal2(x*scalar,y*scalar);
}

Normal2 &Normal2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Normal2 Normal2::operator/(float scalar) const
{
	float i = Math::inverse(scalar);
	return Normal2(x*i,y*i);
}

Normal2 &Normal2::operator/=(float scalar)
{
	float i = Math::inverse(scalar);
	x *= i;
	y *= i;
	return *this;
}

bool Normal2::operator==(const Normal2 &n) const
{
	return x == n.x && y == n.y;
}

bool Normal2::operator!=(const Normal2 &n) const
{
	return x != n.x || y != n.y;
}

//stream output
std::ostream &operator<<(std::ostream &out,const Normal2 &n)
{
	out << n.x << ',' << n.y;
	return out;
}

float Normal2::dot(const Normal2 &n) const { return x*n.x + y*n.y; }

float Normal2::dot(const Vector2 &v) const { return x*v.x + y*v.y; }

float Normal2::length() const { return Math::sqrt(x*x + y*y); }

float Normal2::lengthSquared() const { return x*x + y*y; }

void Normal2::normalize()
{
	float invLength = Math::inverse(length());
	x *= invLength;
	y *= invLength;
}

//computes the tangent vector to this normal.
//performs a counterclockwise rotation
Vector2 Normal2::tangent() const
{
	return Vector2(-y,x);
}

//test
#ifdef DEBUG
void Normal2::test()
{
	std::cout << "Normal2 tests" << std::endl;
	std::cout << "Normal2::length(1,1) -> should return 1.414: " << Normal2(1,1).length() << std::endl;
	std::cout << "Normal2::lengthSquared(1,1) -> should return 2: " << std::endl;
	std::cout << "Normal2::tangent(2,1): " << Normal2(2,1).tangent() << std::endl;
	Normal2 n(2,2);
	std::cout << "before normalizing: " << n << std::endl;
	n.normalize();
	std::cout << "after normalizing: " << n << std::endl;
	std::cout << std::endl;
}
#endif

}
