//local dependencies
#include <entropy\physics\r2\force2.h>
#include <entropy\math\math.h>

namespace entropy
{

void Gravity2::updateForce(DynamicObject2 &obj,float t)
{
	obj.addForce(gravity * obj.getMass());
}

void Drag2::updateForce(DynamicObject2 &obj,float t)
{
	Vector2 force = obj.getVelocity();

	//calculate the total drag coefficient
	float dragCoeff = force.length();
	if(Math::isZero(dragCoeff))
	{
		return; //zero velocity, no force
	}
	dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

	//calculate the final force and apply it
	force.normalize();
	force *= -dragCoeff;
	obj.addForce(force);
}

void Newton2::updateForce(DynamicObject2 &obj,float t)
{
	obj.addForce(direction * magnitude);
}

}
