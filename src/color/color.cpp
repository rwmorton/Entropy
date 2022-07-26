//local dependencies
#include <entropy\color\color.h>
#include <entropy\math\math.h>

namespace entropy
{

//static variable definitions
const Color Color::RED(1.0f,0.0f,0.0f);
const Color Color::GREEN(0.0f,1.0f,0.0f);
const Color Color::BLUE(0.0f,0.0f,1.0f);
const Color Color::BLACK(0.0f,0.0f,0.0f);
const Color Color::WHITE(1.0f,1.0f,1.0f);

Color::Color(const Color &right)
{
	r = right.r;
	g = right.g;
	b = right.b;
}

Color &Color::operator=(const Color &c)
{
	r = c.r;
	g = c.g;
	b = c.b;
	return *this;
}

Color::operator float*()
{
	return &r;
}

float &Color::operator[](int i)
{
	ASSERT(i >= 0 && i <= 2);
	return *((&r) + i);
}

Color Color::operator+(const Color &c) const
{
	return Color(r+c.r,g+c.g,b+c.b);
}

Color Color::operator+=(const Color &c)
{
	r += c.r;
	g += c.g;
	b += c.b;
	return *this;
}

Color Color::operator-() const
{
	return Color(-r,-g,-b);
}

Color Color::operator-(const Color &c) const
{
	return Color(r-c.r,g-c.g,b-c.b);
}

Color Color::operator-=(const Color &c)
{
	r -= c.r;
	g -= c.g;
	b -= c.b;
	return *this;
}

Color Color::operator*(float scalar) const
{
	return Color(r*scalar,g*scalar,b*scalar);
}

Color &Color::operator*=(float scalar)
{
	r *= scalar;
	g *= scalar;
	b *= scalar;
	return *this;
}

Color Color::operator/(float scalar) const
{
	float i = Math::inverse(scalar);
	return Color(r*i,g*i,b*i);
}

Color &Color::operator/=(float scalar)
{
	float i = Math::inverse(scalar);
	r *= i;
	g *= i;
	b *= i;
	return *this;
}

bool Color::operator==(const Color &c) const
{
	return r == c.r && g == c.g && b == c.b;
}

bool Color::operator!=(const Color &c) const
{
	return r != c.r || g != c.g || b != c.b;
}

//stream output
std::ostream &operator<<(std::ostream &out,const Color &c)
{
	out << c.r << ',' << c.g << ',' << c.b;
	return out;
}

//test
#ifdef DEBUG
void Color::test()
{
	std::cout << "Color tests" << std::endl;
	std::cout << std::endl;
}
#endif

}
