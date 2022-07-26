#ifndef __particleForceRegistry3_h__
#define __particleForceRegistry3_h__

//local dependencies
#include <entropy\physics\r3\particleForceGenerator3.h>

namespace entropy
{

//holds all the force generators and the particles they affect
class ParticleForceRegistry3
{
public:
	//methods
	void add(Particle3 *particle,ParticleForceGenerator3 *fg);
	void remove(Particle3 *particle,ParticleForceGenerator3 *fg);
	void clear();
	void updateForces(float t);
private:
	//
protected:
	//keeps track of a force generator
	//and the particle it affects
	struct ParticleForceRegistration
	{
		Particle3 *particle;
		ParticleForceGenerator3 *fg;
	};
	//holds the list of registrations
	typedef std::vector<ParticleForceRegistration> Registry;
	Registry registry;
};

}

#endif
