#ifndef __steeringOutput_h__
#define __steeringOutput_h__

//local dependencies
#include <entropy\math\r3\vector3.h>

namespace entropy
{

class SteeringOutput
{
public:
	//constructors
	SteeringOutput() : angular(0.0f) {}
	SteeringOutput(const Vector2 &linear,float angular=0.0f) : linear(linear),angular(angular) {}
	//methods
	void clear()
	{
		linear = Vector2::ZERO;
		angular = 0.0f;
	}
	//variables
	Vector2 linear;
	float angular;
};

}

#endif
