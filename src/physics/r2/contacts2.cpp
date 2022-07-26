//local dependencies
#include <entropy\physics\r2\contacts2.h>
#include <entropy\math\math.h>

namespace entropy
{

void ParticleContact2::resolveVelocity(float t)
{
	//find the velocity in the direction of the contact
	float separatingVelocity = calculateSeparatingVelocity();

	//check if it needs to be resolved
	if(separatingVelocity > 0)
	{
		//the contact is either separating, or
		//stationary, there's no impulse required
		return;
	}

	//calculate the new separating velocity
	float newSepVelocity = -separatingVelocity * restitution;

	//check the velocity build up due to acceleration only
	Vector2 accCausedVelocity = particle[0]->getAcceleration();
	if(particle[1])
	{
		accCausedVelocity -= particle[1]->getAcceleration();
	}
	float accCausedBySepVelocity = accCausedVelocity.dot(contactNormal) * t;

	//if we've got a closing velocity due to acceleration
	//buildup, remove it from teh new separating velocity
	if(accCausedBySepVelocity < 0)
	{
		newSepVelocity += restitution * accCausedBySepVelocity;

		//make sure we haven't removed more
		//than was there to remove
		if(newSepVelocity < 0)
		{
			newSepVelocity = 0;
		}
	}

	float deltaVelocity = newSepVelocity - separatingVelocity;

	//we apply the change in velocity to each object in proportion
	//to their inverse mass (ie. those with lower inverse mass
	//get less change in velocity)...
	float totalMass = particle[0]->getMass();
	if(particle[1])
	{
		totalMass += particle[1]->getMass();
	}

	//if all particles have infinite mass, then impulses have no effect
	float totalInverseMass = Math::inverse(totalMass);
	if(totalInverseMass <= 0)
	{
		return;
	}

	//calculate impulse to apply
	float impulse = deltaVelocity / totalInverseMass;

	//find the amount of impulse per unit of inverse mass
	Vector2 impulsePerIMass = contactNormal * impulse;

	//apply impulses; they are applied in the direction of
	//the contact, and are proportional to the inverse mass
	particle[0]->setVelocity(particle[0]->getVelocity() + impulsePerIMass * Math::inverse(particle[0]->getMass()));
	if(particle[1])
	{
		//goes in the opposite direction
		particle[1]->setVelocity(particle[1]->getVelocity() + impulsePerIMass * -Math::inverse(particle[1]->getMass()));
	}
}

void ParticleContact2::resolveInterpenetration(float t)
{
	//if we don't have interpenetration, then skip this step
	if(penetration <= 0)
	{
		return;
	}

	//the movement of each object is based on their
	//inverse mass, so total that
	float totalMass = particle[0]->getMass();
	if(particle[1])
	{
		totalMass += particle[1]->getMass();
	}
	float totalInverseMass = Math::inverse(totalMass);

	//if all particles have infinite mass, then we do nothing
	if(totalInverseMass <= 0)
	{
		return;
	}

	//find the amount of penetration resolution per unit of inverse mass
	Vector2 movePerIMass = contactNormal * (penetration / totalInverseMass);

	//calculate the movement amounts
	particleMovement[0] = movePerIMass * Math::inverse(particle[0]->getMass());
	if(particle[1])
	{
		//reverse
		particleMovement[1] = movePerIMass * -Math::inverse(particle[1]->getMass());
	}
	else
	{
		//clear
		particleMovement[1] = Vector2::ZERO;
	}

	//apply the penetration resolution
	particle[0]->setPosition(particle[0]->getPosition() + particleMovement[0]);
	if(particle[1])
	{
		particle[1]->setPosition(particle[1]->getPosition() + particleMovement[1]);
	}
}

void ParticleContact2::resolve(float t)
{
	resolveVelocity(t); //generate impulse
	resolveInterpenetration(t);
}

float ParticleContact2::calculateSeparatingVelocity() const
{
	Vector2 relativeVelocity = particle[0]->getVelocity();
	if(particle[1])
	{
		relativeVelocity -= particle[1]->getVelocity();
	}
	return relativeVelocity.dot(contactNormal);
}

ParticleContactResolver2::ParticleContactResolver2(unsigned iterations) : iterations(iterations) {}

void ParticleContactResolver2::setIterations(unsigned iterations)
{
	this->iterations = iterations;
}

void ParticleContactResolver2::resolveContacts(ParticleContact2 *contactArray,unsigned numContacts,float t)
{
	iterationsUsed = 0;
	while(iterationsUsed < iterations)
	{
		//find the contact with the largest closing velocity
		float max = Math::MAX;
		unsigned maxIndex = numContacts;
		for(unsigned i=0; i<numContacts; i++)
		{
			float sepVel = contactArray[i].calculateSeparatingVelocity();
			if(sepVel < max && (sepVel < 0 || contactArray[i].penetration > 0))
			{
				max = sepVel;
				maxIndex = i;
			}
		}

		//do we have anything worth resolving?
		if(maxIndex == numContacts)
		{
			break;
		}

		//resolve this contact
		contactArray[maxIndex].resolve(t);

		//update the interpenetrations for all particles
		Vector2 *move = contactArray[maxIndex].particleMovement;
		for(unsigned i=0; i<numContacts; i++)
		{
			if(contactArray[i].particle[0] == contactArray[maxIndex].particle[0])
			{
				contactArray[i].penetration -= move[0].dot(contactArray[i].contactNormal);
			}
			else if(contactArray[i].particle[0] == contactArray[maxIndex].particle[1])
			{
				contactArray[i].penetration -= move[1].dot(contactArray[i].contactNormal);
			}
			if(contactArray[i].particle[1])
			{
				if(contactArray[i].particle[1] == contactArray[maxIndex].particle[0])
				{
					contactArray[i].penetration += move[0].dot(contactArray[i].contactNormal);
				}
				else if(contactArray[i].particle[1] == contactArray[maxIndex].particle[1])
				{
					contactArray[i].penetration += move[1].dot(contactArray[i].contactNormal);
				}
			}
		}

		iterationsUsed++;
	}
}

float ParticleLink2::currentLength() const
{
	return particle[0]->getPosition().distance(particle[1]->getPosition());
}

unsigned ParticleRod2::fillContact(ParticleContact2 *contact,unsigned limit) const
{
	//find the length of the rod
	float currentLen = currentLength();

	//check whether we're overextended
	if(currentLen == length)
	{
		return 0;
	}

	//otherwise return the contact
	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];

	//calculate the normal
	Normal2 normal = particle[1]->getPosition() - particle[0]->getPosition();
	normal.normalize();

	//the contact normal depends on whether we're
	//extending or compressing
	if(currentLen > length)
	{
		contact->contactNormal = normal;
		contact->penetration = currentLen - length;
	}
	else
	{
		contact->contactNormal = -normal;
		contact->penetration = length - currentLen;
	}

	//always use zero restitution
	contact->restitution = 0;

	return 1;
}

ParticleWorld2::ParticleWorld2(unsigned maxContacts,unsigned iterations) : resolver(iterations),maxContacts(maxContacts)
{
	contacts = new ParticleContact2[maxContacts];
	calculateIterations = (iterations == 0);
}

ParticleWorld2::~ParticleWorld2()
{
	delete[] contacts;
}

unsigned ParticleWorld2::generateContacts()
{
	unsigned limit = maxContacts;
	ParticleContact2 *nextContact = contacts;

	for(ContactGenerators::iterator g = contactGenerators.begin(); g != contactGenerators.end(); g++)
	{
		unsigned used = (*g)->addContact(nextContact,limit);
		limit -= used;
		nextContact += used;

		if(limit <= 0)
		{
			break;
		}
	}

	return maxContacts - limit;
}

void ParticleWorld2::integrate(float t)
{
	Particles::iterator p = particles.begin();
	while(p != particles.end())
	{
		if(forces.size() > 0)
		{
			Forces::iterator f = forces.begin();
			while(f != forces.end())
			{
				(*f)->updateForce(*(*p),t);

				f++;
			}
		}
		(*p)->integrate(t);

		p++;
	}
}

void ParticleWorld2::runPhysics(float t)
{
	integrate(t);

	unsigned usedContacts = generateContacts();

	if(usedContacts)
	{
		if(calculateIterations)
		{
			resolver.setIterations(usedContacts * 2);
		}
		resolver.resolveContacts(contacts,usedContacts,t);
	}
}

void ParticleWorld2::startFrame()
{
	for(Particles::iterator p = particles.begin(); p!= particles.end(); p++)
	{
		(*p)->clearForces();
	}
}

ParticleWorld2::Particles &ParticleWorld2::getParticles()
{
	return particles;
}

ParticleWorld2::ContactGenerators &ParticleWorld2::getContactGenerators()
{
	return contactGenerators;
}

void GroundContacts2::init(ParticleWorld2::Particles *particles)
{
	GroundContacts2::particles = particles;
}

unsigned GroundContacts2::addContact(ParticleContact2 *contact,unsigned limit) const
{
	unsigned count = 0;
	for(ParticleWorld2::Particles::iterator p = particles->begin(); p != particles->end(); p++)
	{
		float x = (*p)->getPosition().x;
		float y = (*p)->getPosition().y;
		if(y < groundY && x >= xMin && x <= xMax)
		{
			contact->contactNormal = Vector2::Y_AXIS;
			contact->particle[0] = *p;
			contact->particle[1] = 0;
			contact->penetration = Math::abs(groundY - y);
			contact->restitution = 0.2f;
			contact++;
			count++;
		}

		if(count >= limit)
		{
			return count;
		}
	}
	return count;
}

void WallContacts2::init(ParticleWorld2::Particles *particles)
{
	WallContacts2::particles = particles;
}

unsigned WallContacts2::addContact(ParticleContact2 *contact,unsigned limit) const
{
	unsigned count = 0;
	for(ParticleWorld2::Particles::iterator p = particles->begin(); p != particles->end(); p++)
	{
		float x = (*p)->getPosition().x;
		//Vector2 w_v = Vector2(wallX,0.0f);
		//Vector2 p_v = Vector2((*p)->getPosition().x,(*p)->getPosition().y);
		//Vector2 v = -(w_v - p_v);
		//if(v.dot(normal) < 0)
		if((wallX < 0 && x < wallX) || (wallX > 0 && x > wallX))
		{
			contact->contactNormal = normal;
			contact->particle[0] = *p;
			contact->particle[1] = 0;
			contact->penetration = Math::abs(wallX - x);
			contact->restitution = 0.5f;
			contact++;
			count++;
		}

		if(count >= limit)
		{
			return count;
		}
	}
	return count;
}


}
