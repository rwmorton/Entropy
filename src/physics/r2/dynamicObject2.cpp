//local dependencies
#include <entropy\physics\r2\dynamicObject2.h>
#include <entropy\math\math.h>

namespace entropy
{

DynamicObject2::DynamicObject2() : mass(1.0f) {}

DynamicObject2::DynamicObject2
(
	const Point2 &position,
	const Vector2 &velocity,
	const Vector2 &acceleration,
	float mass
) : position(position),velocity(velocity),acceleration(acceleration)
{
	ASSERT(!Math::isZero(mass)); //prevent divide by zero
	this->mass = mass;
}

Point2 DynamicObject2::getPosition() const
{
	return position;
}

void DynamicObject2::setPosition(const Point2 &p)
{
	position = p;
}

Vector2 DynamicObject2::getVelocity() const
{
	return velocity;
}

void DynamicObject2::setVelocity(const Vector2 &v)
{
	velocity = v;
}

Vector2 DynamicObject2::getAcceleration() const
{
	return acceleration;
}

void DynamicObject2::setAcceleration(const Vector2 &a)
{
	acceleration = a;
}

float DynamicObject2::getMass() const
{
	return mass;
}

void DynamicObject2::setMass(float m)
{
	ASSERT(!Math::isZero(m)); //prevent divide by zero
	mass = m;
}

void DynamicObject2::clearForces()
{
	accumulatedForces = Vector2::ZERO;
}

void DynamicObject2::addForce(const Vector2 &force)
{
	accumulatedForces += force;
}

}
