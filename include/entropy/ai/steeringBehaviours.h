#ifndef __steeringBehaviours_h__
#define __steeringBehaviours_h__

//local dependencies
#include <entropy\math\r2\point2.h>
#include <entropy\math\r2\vector2.h>
#include <entropy\ai\steeringOutput.h>
#include <entropy\ai\entity.h>

namespace entropy
{

//forward declarations
class Vehicle;

class SteeringBehaviours
{
public:
	//constructor
	SteeringBehaviours(Vehicle *agent=0);
	//methods
	void seek();
	void flee();
	void arrive();
	void pursuit(const Vehicle *evader);
	void evade(const Vehicle *pursuer);
	void wander();
	void obstacleAvoidance(std::vector<Entity> &obstacles);
	Vector2 getSteering();
	//variables
	//NOTE: have left these public access as this is just
	//a test framework, and i gain nothing from forcing
	//private scope
	Vehicle *vehicle;
	//the current target
	Point2 *target;
	//these can be used to keep track of
	//friends, pursuers or prey
	Point2 *targetAgent1,*targetAgent2;
	//how fast should a vehicle deccelerate?
	float deceleration;
	//wander
	Vector2 wanderDirection;	//direction to wander
	Point2 wanderTarget;		//wander target pos
	float wanderRadius;			//radius of the constraining circle
	float wanderDistance;		//distance offset of circle from agent
	float wanderJitter;			//maximum amount of random displacement added to target per second
	//behaviour weights
	float evadeDistance;
	float seekWeight;
	float fleeWeight;
	float arriveWeight;
	float pursuitWeight;
	float evadeWeight;
	float wanderWeight;
private:
	//variables
	//the steering force created by the
	//combined effect of all the steering behaviours
	Vector2 steeringForce;
};

}

#endif
