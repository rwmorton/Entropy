#ifndef __dynamicObject2_h__
#define __dynamicObject2_h__

//local dependencies
#include <entropy\cfg.h>
#include <entropy\math\r2\transform2.h>
#include <entropy\math\r2\point2.h>
#include <entropy\math\r2\vector2.h>

namespace entropy
{

//abstract base class for 2 dimensional dynamic objects
//ie. particles and rigid bodies
class DynamicObject2
{
public:
	//destructor
	virtual ~DynamicObject2() {}
	//methods
	Point2 getPosition() const;
	void setPosition(const Point2 &p);
	Vector2 getVelocity() const;
	void setVelocity(const Vector2 &v);
	Vector2 getAcceleration() const;
	void setAcceleration(const Vector2 &a);
	float getMass() const;
	void setMass(float m);
	void clearForces();
	void addForce(const Vector2 &force);
	virtual Transform2 getWorldTransform() const = 0;
	virtual void integrate(float t) = 0;
	#ifdef DEBUG
	virtual void debugRender() = 0;
	#endif
private:
	//
protected:
	//constructors
	DynamicObject2();
	DynamicObject2
	(
		const Point2 &position,
		const Vector2 &velocity,
		const Vector2 &acceleration,
		float mass
	);
	//variables
	Point2 position;			//position of the object in world space
	Vector2 velocity;			//its velocity
	Vector2 acceleration;		//and acceleration
	float mass;					//mass of this object
	Vector2 accumulatedForces;	//all forces acting on this object
	Transform2 localToWorld;	//the local to world transform for this object
};

}

#endif
