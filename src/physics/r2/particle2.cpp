//local dependencies
#include <entropy\physics\r2\particle2.h>
#include <entropy\math\math.h>

namespace entropy
{

Transform2 Particle2::getWorldTransform() const
{
	return Transform2::translate(Vector2(position.x,position.y));
}

//integrate the particle forward in time by t.
//uses a Newton-Euler integration method which
//is a linear approximation of the correct integral
void Particle2::integrate(float t)
{
	ASSERT(!Math::isZero(t));

	//compute acceleration from
	//the accumulated forces
	Vector2 resultingAcceleration = acceleration;
	resultingAcceleration += accumulatedForces / mass;

	//update linear velocity from the acceleration
	//vf = vi + at
	velocity += resultingAcceleration * t;

	//update linear position
	//we ignore the time squared in the position
	//kinematic equation as the time step is likely
	//to be negligible.
	//pf = pi + vt + 0.5at^2 -> pf = pi + vt
	position += velocity * t;

	//clear accumulated forces
	accumulatedForces = Vector2::ZERO;
}

#ifdef DEBUG
//render particles (useful for debugging)
void Particle2::debugRender()
{
	glBegin(GL_POINTS);
	glVertex3fv(position);
	glEnd();
}
#endif

}
