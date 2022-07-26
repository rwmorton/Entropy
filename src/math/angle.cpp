//local dependencies
#include <entropy\math\angle.h>
#include <entropy\math\math.h>

namespace entropy
{

//static variable definitions
const Angle Angle::ZERO(0.0f);
const Angle Angle::PI(Math::PI);
const Angle Angle::HALF_PI(Math::HALF_PI);
const Angle Angle::TWO_PI(Math::TWO_PI);

Angle::Angle() : angle(0.0f),unit(Angle::RADIANS) {}

Angle::Angle(float angle,Unit unit) : angle(angle),unit(unit) {}

Angle::Angle(const Angle &right)
{
	angle = right.angle;
	unit = right.unit;
}

Angle &Angle::operator=(const Angle &a)
{
	angle = a.angle;
	unit = a.unit;
	return *this;
}

std::ostream &operator<<(std::ostream &out,const Angle &a)
{
	out << a.angle;
	switch(a.unit)
	{
		case Angle::RADIANS:
			out << " radians";
			break;
		case Angle::DEGREES:
			out << " degrees";
	}
	return out;
}

Angle::Unit Angle::getUnit() const
{
	return unit;
}

void Angle::setUnit(Unit unit)
{
	this->unit = unit;
}

float Angle::asRadians() const
{
	return (unit == Angle::RADIANS ? angle : angle * Math::DEG_TO_RAD);
}

float Angle::asDegrees() const
{
	return (unit == Angle::DEGREES ? angle : angle * Math::RAD_TO_DEG);
}

#ifdef DEBUG
void Angle::test()
{
	Angle a(Math::PI);
	Angle b(45.0f,Angle::DEGREES);
	std::cout << "Angle tests" << std::endl;
	std::cout << "Angle a is Pi radians: " << a << std::endl;
	std::cout << "Angle b is 45 degrees: " << b << std::endl;
	std::cout << "Angle a as degrees: " << a.asDegrees() << std::endl;
	std::cout << "Angle b as radians: " << b.asRadians() << std::endl;
	std::cout << std::endl;
}
#endif

}
