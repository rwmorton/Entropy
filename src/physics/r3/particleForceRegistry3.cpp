//local dependencies
#include <entropy\physics\r3\particleForceRegistry3.h>

namespace entropy
{

//register the given force generator to affect the given particle
void ParticleForceRegistry3::add(Particle3 *particle,ParticleForceGenerator3 *fg)
{
	ParticleForceRegistry3::ParticleForceRegistration registration;
	registration.particle = particle;
	registration.fg = fg;
	registry.push_back(registration);
}

//remove the given registered pair. if the pair is not
//registered then this method will have no effect
void ParticleForceRegistry3::remove(Particle3 *particle,ParticleForceGenerator3 *fg)
{	
	Registry::iterator i = registry.begin();
	while(i != registry.end())
	{
		if(i->particle == particle && i->fg == fg)
		{
			i = registry.erase(i);
		}

		i++; //next pair
	}
}

//clears all registered pairs. it will not affect the particles
//or force generators, just the record of their connection
void ParticleForceRegistry3::clear()
{
	registry.clear();
}

//updates all the force generators which add the result to their particle
void ParticleForceRegistry3::updateForces(float t)
{
	Registry::iterator i = registry.begin();
	while(i != registry.end())
	{
		i->fg->updateForce(*(i->particle),t);

		i++; //next pair
	}
}

}
