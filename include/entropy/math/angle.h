#ifndef __angle_h__
#define __angle_h__

//local dependencies
#include <entropy\cfg.h>

namespace entropy
{

//Angle class. Helpful for quick unit
//conversions (radians/degrees).
//Defaults to radian units
class Angle
{
public:
	//angle unit
	enum Unit
	{
		RADIANS,
		DEGREES
	};
	//constructors
	Angle();
	Angle(float angle,Unit unit=RADIANS);
	Angle(const Angle &right);
	//destructor
	~Angle() {}
	//operator overloads
	Angle &operator=(const Angle &a);

	//TODO .. +,-,+=,-=,*,*=,/,/=,!=,==,<,>,<=,>=

	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Angle &a);
	//methods
	Unit getUnit() const;
	void setUnit(Unit unit);
	float asRadians() const;
	float asDegrees() const;
	//static methods
	#ifdef DEBUG
		static void test();
	#endif
	//static variables
	static const Angle ZERO;
	static const Angle PI;
	static const Angle HALF_PI;
	static const Angle TWO_PI;
private:
	//variables
	float angle;
	Unit unit;
protected:
	//
};

}

#endif
