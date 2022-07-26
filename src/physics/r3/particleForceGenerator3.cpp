//local dependencies
#include <entropy\physics\r3\particleForceGenerator3.h>
#include <entropy\math\math.h>

namespace entropy
{

void ParticleGravity3::updateForce(Particle3 &particle,float t)
{
	particle.addForce(gravity);
}

void ParticleDrag3::updateForce(Particle3 &particle,float t)
{
	ASSERT(!Math::isZero(t));

	Vector3 force = particle.getVelocity();

	//calculate the total drag coefficient
	float dragCoeff = force.length();
	dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

	//calculate the final force and add it to the particle
	force.normalize();
	force *= -dragCoeff;
	particle.addForce(force);
}

void ParticleSpring3::updateForce(Particle3 &particle,float t)
{
	ASSERT(!Math::isZero(t));

	//calculate the spring force vector
	Vector3 force = particle.getPosition() - other->getPosition();

	//calculate the magnitude of the force
	float mag = force.length();
	mag = Math::abs(mag - restLength);
	mag *= springConstant;

	//calculate the final force and apply it
	force.normalize();
	force *= -mag;
	particle.addForce(force);
}

void ParticleBuoyancy3::updateForce(Particle3 &particle,float t)
{
	ASSERT(!Math::isZero(t));

	//caculate the submersion depth
	float depth = particle.getPosition().y;

	//check if we're out of the water
	if(depth >= waterHeight)
	{
		return;
	}
	Vector3 force;

	//check if we're at maximum depth
	if(depth <= waterHeight - maxDepth)
	{
		force.y = liquidDensity * volume;
		particle.addForce(force);
		return;
	}

	//otherwise we are partly submerged
	//force.y = liquidDensity * volume * (depth - maxDepth - waterHeight) / (2.0f * maxDepth);
	float mult = depth / (waterHeight - maxDepth);
	force.y = liquidDensity * volume * mult;
	particle.addForce(force);
}

}
