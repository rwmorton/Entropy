#ifndef __particle_h__
#define __particle_h__

//local dependencies
#include <entropy\math\r3\point3.h>
#include <entropy\math\r3\vector3.h>

namespace entropy
{

class Particle3
{
public:
	//constructors
	Particle3();
	Particle3(float mass,float damping=1.0f);
	//methods
	void setPosition(const Point3 &position);
	Point3 getPosition() const;
	void setVelocity(const Vector3 &velocity);
	Vector3 getVelocity() const;
	void setAcceleration(const Vector3 &acceleration);
	Vector3 getAcceleration() const;
	void setMass(float mass);
	float getMass() const;
	void setDamping(float damping);
	float getDamping() const;
	void addForce(Vector3 force);
	void clearForces();
	void integrate(float t);
	void render(float size=1.0f);
private:
	//variables
	Point3 position;			//position of particle
	Vector3 velocity;			//velocity of particle
	Vector3 acceleration;		//acceleration of particle
	//accumulated forces acting on the particle.
	Vector3 accumulatedForces;
	//inverse mass of the particle - need this to
	//calculate responses to force. zero masses are invalid
	//we pass a value for mass and it will get turned into
	//its reciprocal form (ie. the inverse)
	float inverseMass;
	//holds the amount of damping applied to linear
	//motion. damping is require to remove energy added
	//through numerical instability in the integrtor
	//a value of 0 means we remove all the velocity
	//a value of 1 is the same as no damping
	float damping;
protected:
	//
};

}

#endif
