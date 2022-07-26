//local dependencies
#include <entropy\math\r2\point2.h>
#include <entropy\math\r2\vector2.h>
#include <entropy\math\math.h>

namespace entropy
{

//static variable definitions
const Point2 Point2::ZERO(0.0f,0.0f);
const Point2 Point2::X_AXIS(1.0f,0.0f);
const Point2 Point2::Y_AXIS(0.0f,1.0f);

Point2::Point2(const Point2 &right)
{
	x = right.x;
	y = right.y;
}

Point2 &Point2::operator=(const Point2 &p)
{
	x = p.x;
	y = p.y;
	return *this;
}

Point2::operator float*()
{
	return &x;
}

float &Point2::operator[](int i)
{
	ASSERT(i >= 0 && i <= 1);
	return *((&x) + i);
}

//it doesn't make sense to add points, but a vector
//can be added to a point to give a new point
Point2 Point2::operator+(const Vector2 &v) const
{
	return Point2(x+v.x,y+v.y);
}

//a vector can be added to a point
Point2 Point2::operator+=(const Vector2 &v)
{
	x += v.x;
	y += v.y;
	return *this;
}

//a point subtracted from a point gives a vector
Vector2 Point2::operator-(const Point2 &p) const
{
	return Vector2(x-p.x,y-p.y);
}

//same as addition, except that v = (-v)
Point2 Point2::operator-(const Vector2 &v) const
{
	return Point2(x-v.x,y-v.y);
}

Point2 Point2::operator-=(const Vector2 &v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Point2 Point2::operator*(float scalar) const
{
	return Point2(x*scalar,y*scalar);
}

Point2 &Point2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Point2 Point2::operator/(float scalar) const
{
	float i = Math::inverse(scalar);
	return Point2(x*i,y*i);
}

Point2 &Point2::operator/=(float scalar)
{
	float i = Math::inverse(scalar);
	x *= i;
	y *= i;
	return *this;
}

bool Point2::operator==(const Point2 &p) const
{
	return x == p.x && y == p.y;
}

bool Point2::operator!=(const Point2 &p) const
{
	return x != p.x || y != p.y;
}

//stream output
std::ostream &operator<<(std::ostream &out,const Point2 &p)
{
	out << p.x << ',' << p.y;
	return out;
}

float Point2::distance(const Point2 &p) const
{
	float a = x - p.x;
	float b = y - p.y;
	return Math::sqrt(a*a + b*b);
}

float Point2::distanceSquared(const Point2 &p) const
{
	float a = x - p.x;
	float b = y - p.y;
	return a*a + b*b;
}

//test
#ifdef DEBUG
void Point2::test()
{
	std::cout << "Point2 tests" << std::endl;
	std::cout << "Point2::distance([0,0],[5,5]) -> should return: 7.071: " << Point2(0,0).distance(Point2(5,5)) << std::endl;
	std::cout << "Point2::distance([-2.5,-2.5],[2.5,2.5]) -> should return: 7.071: " << Point2(-2.5f,-2.5f).distance(Point2(2.5,2.5)) << std::endl;
	std::cout << "Point2::distanceSquared([0,0],[5,5]) -> should return: 50: " << Point2(0,0).distanceSquared(Point2(5,5)) << std::endl;
	std::cout << "Point2::distanceSquared([-2.5,-2.5],[2.5,2.5]) -> should return: 50: " << Point2(-2.5f,-2.5f).distanceSquared(Point2(2.5,2.5)) << std::endl;
	std::cout << std::endl;
}
#endif

}
