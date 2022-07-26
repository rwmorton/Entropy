#ifndef __contacts2_h__
#define __contacts2_h__

//local dependencies
#include <entropy\physics\r2\particle2.h>
#include <entropy\physics\r2\force2.h>
#include <entropy\math\r2\vector2.h>
#include <entropy\math\r2\normal2.h>
#include <entropy\math\math.h>

namespace entropy
{

//forward declaration
class ParticleContactResolver2;

//represents two particles in contact
class ParticleContact2
{
public:
	//friends
	friend ParticleContactResolver2;
	//holds the particles involved in the contact. the
	//second can be null for contacts with static objects
	Particle2 *particle[2];
	//holds the normal restitution coefficient at the contact
	float restitution;
	//holds the direction of the contact in world coordinates
	Normal2 contactNormal;
	//holds the depth of penetration at the contact
	float penetration;
	//the amount each particle is to be moved by during interpenetration resolution
	Vector2 particleMovement[2];
private:
	//handles the impulse calculations for this collision
	void resolveVelocity(float t);
	//handles the interpenetration resolution for this contact
	void resolveInterpenetration(float t);
protected:
	//resolves this contact, for both velocity and interpenetration
	void resolve(float t);
	//calculates the separating velocity at this contact
	float calculateSeparatingVelocity() const;
};

//the contact resolution routine for particle contacts. one
//resolver instance can be shared for the whole simulation
class ParticleContactResolver2
{
public:
	//constructor
	ParticleContactResolver2(unsigned iterations);
	//methods
	//sets the number of iterations that can be used
	void setIterations(unsigned iterations);
	//Resolves a set of particle contacts for both penetration and
	//velocity.
	//Contacts that cannot interact with each other should be passed
	//to separate calls to resolve contacts, as the resolution
	//algorithm takes much longer for lots of contacts than it does
	//for the same number of contacts in small sets.
	void resolveContacts(ParticleContact2 *contactArray,unsigned numContacts,float t);
private:
	//
protected:
	//variables
	unsigned iterations;		//number of iterations allowed
	unsigned iterationsUsed;	//track number of iterations used
};

//interface for contact generators applying to particles
class ParticleContactGenerator2
{
public:
	//Fills the g iven contact structure with the generated
	//contact. The contact pointer should point to the first
	//available contact in a contact array, where limit is
	//the maximum number of contacts in the array that can
	//be written to. The method returns the number of contacts
	//that have been written.
	virtual unsigned addContact(ParticleContact2 *contact,unsigned limit) const = 0;
};

//Links connect two particles together, generating a contact if
//they violate the constraints of their link. It is used as a
//base class for cables and rods, and could be used as a base
//class for springs with a limit to their extension.
class ParticleLink2
{
public:
	//Fills the given contact structure with the contact needed
	//to keep this link from violating its constraint. The contact
	//pointer should point to the first available contact in a
	//contact array, where limit is the maximum number of contacts
	//in the array that can be written to. The method returns the
	//number of contacts that have been written. This format is so
	//common to contact-generating functions, but this class can
	//only generate a single contact, so the pointer can be a pointer
	//to a single element. The limit parameter is assumed to be at
	//least one (zero isn't valid), and the return value is either
	//0, if the cable wasn't overextended, or one if a contact was needed.
	virtual unsigned fillContact(ParticleContact2 *contact,unsigned limit) const = 0;
protected:
	//methods
	float currentLength() const;
	//variables
	Particle2 *particle[2];
};

//Rods link a pair of particles, generating a contact if they
//stray too far apart or too close.
class ParticleRod2 : public ParticleLink2
{
public:
	//methods
	virtual unsigned fillContact(ParticleContact2 *contact,unsigned limit) const;
	//variables
	float length;
};

class ParticleWorld2
{
public:
	typedef std::vector<Particle2 *> Particles;
	typedef std::vector<Force2 *> Forces;
	typedef std::vector<ParticleContactGenerator2 *> ContactGenerators;
	//constructor
	ParticleWorld2(unsigned maxContacts,unsigned iterations=0);
	//destructor
	~ParticleWorld2();
	//methods
	unsigned generateContacts();
	void integrate(float t);
	void runPhysics(float t);
	void startFrame();
	Particles &getParticles();
	ContactGenerators &getContactGenerators();
private:
	//
protected:
	Particles particles;
	Forces forces;
	bool calculateIterations;
	ParticleContactResolver2 resolver;
	ContactGenerators contactGenerators;
	ParticleContact2 *contacts;
	unsigned maxContacts;
};

//ground contact generator
class GroundContacts2 : public ParticleContactGenerator2
{
public:
	//constructor
	GroundContacts2(float y=0.0f,float xmin=-Math::MAX,float xmax=Math::MAX) : groundY(y),xMin(xmin),xMax(xmax) {}
	//methods
	void init(ParticleWorld2::Particles *particles);
	virtual unsigned addContact(ParticleContact2 *contact,unsigned limit) const;
private:
	float groundY;
	float xMin,xMax;
	ParticleWorld2::Particles *particles;
};

class WallContacts2 : public ParticleContactGenerator2
{
public:
	//constructor
	WallContacts2(float x,const Vector2 &n) : wallX(x),normal(n) {}
	//methods
	void init(ParticleWorld2::Particles *particles);
	virtual unsigned addContact(ParticleContact2 *contact,unsigned limit) const;
private:
	float wallX;
	Vector2 normal;
	ParticleWorld2::Particles *particles;
};

}

#endif
