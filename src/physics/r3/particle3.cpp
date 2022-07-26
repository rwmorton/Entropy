//local dependencies
#include <entropy\physics\r3\particle3.h>
#include <entropy\cfg.h>
#include <entropy\math\math.h>

namespace entropy
{

Particle3::Particle3() : inverseMass(1.0f),damping(1.0f) {}

Particle3::Particle3(float mass,float damping)
{
	inverseMass = Math::inverse(mass);
	this->damping = damping;
}

void Particle3::setPosition(const Point3 &position)
{
	this->position = position;
}

Point3 Particle3::getPosition() const
{
	return position;
}

void Particle3::setVelocity(const Vector3 &velocity)
{
	this->velocity = velocity;
}

Vector3 Particle3::getVelocity() const
{
	return velocity;
}

void Particle3::setAcceleration(const Vector3 &acceleration)
{
	this->acceleration = acceleration;
}

Vector3 Particle3::getAcceleration() const
{
	return acceleration;
}

void Particle3::setMass(float mass)
{
	this->inverseMass = Math::inverse(mass);
}

float Particle3::getMass() const
{
	return Math::inverse(inverseMass);
}

void Particle3::setDamping(float damping)
{
	this->damping = damping;
}

float Particle3::getDamping() const
{
	return damping;
}

void Particle3::addForce(Vector3 force)
{
	accumulatedForces += force;
}

void Particle3::clearForces()
{
	accumulatedForces = Vector3::ZERO;
}

//integrates the particle forward in time by the given amount.
//this function uses a Newton-Euler integration method, which
//is a linear approximation of the correct integral. for this
//reason it may be inaccurate in some cases
void Particle3::integrate(float t)
{
	ASSERT(!Math::isZero(t));

	//work out the acceleration: F = ma
	Vector3 resultingAcc = acceleration;
	resultingAcc += accumulatedForces * inverseMass;

	//update linear velocity from the acceleration
	//vf = vi + at
	velocity += resultingAcc * t;

	//impose drag
	velocity *= Math::pow(damping,t);

	//update linear position
	//we omit the full version of the equation as
	//the 0.5 * t^2 is likely top be negligible
	//pf = pi + vt + 0.5(at^2)
	position += velocity * t;

	//clear accumulated forces
	accumulatedForces = Vector3::ZERO;
}

void Particle3::render(float size)
{
	glPointSize(size);

	glBegin(GL_POINTS);
	glVertex3fv(position);
	glEnd();

	glPointSize(1.0f);
}

}
