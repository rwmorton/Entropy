#ifndef __particleForceGenerator3_h__
#define __particleForceGenerator3_h__

//local dependencies
#include <entropy\physics\r3\particle3.h>
#include <entropy\math\r3\vector3.h>

namespace entropy
{

//adds force to one or more particles
class ParticleForceGenerator3
{
public:
	//methods
	virtual void updateForce(Particle3 &particle,float t) = 0;
private:
	//
protected:
	//
};

//applies gravitational force
class ParticleGravity3 : public ParticleForceGenerator3
{
public:
	//constructors
	ParticleGravity3(const Vector3 &gravity=Vector3(0.0f,-9.8f,0.0f)) : gravity(gravity) {}
	//methods
	virtual void updateForce(Particle3 &particle,float t);
private:
	//variables
	Vector3 gravity;
protected:
	//
};

//applies drag force
class ParticleDrag3 : public ParticleForceGenerator3
{
public:
	//constructor
	ParticleDrag3(float k1,float k2) : k1(k1),k2(k2) {}
	//methods
	virtual void updateForce(Particle3 &particle,float t);
private:
	//variables
	float k1;	//velocity drag coefficient
	float k2;	//velocity squared drag coefficient
protected:
	//
};

//paticle spring
class ParticleSpring3 : public ParticleForceGenerator3
{
public:
	//constructor
	ParticleSpring3(Particle3 *other,float springConstant,float restLength) : other(other),springConstant(springConstant),restLength(restLength) {}
	//methods
	virtual void updateForce(Particle3 &particle,float t);
private:
	//variables
	Particle3 *other;
	float springConstant;
	float restLength;
protected:
	//
};

//particle buoyancy
class ParticleBuoyancy3 : public ParticleForceGenerator3
{
public:
	//constructor
	ParticleBuoyancy3(float maxDepth,float volume,float waterHeight,float liquidDensity=1000.0f) : maxDepth(maxDepth),volume(volume),waterHeight(waterHeight),liquidDensity(liquidDensity) {}
	//methods
	virtual void updateForce(Particle3 &particle,float t);
private:
	//variables
	float maxDepth;
	float volume;
	float waterHeight;
	float liquidDensity;
protected:
	//
};

}

#endif
