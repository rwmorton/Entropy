#ifndef __vehicle_h__
#define __vehicle_h__

//local dependencies
#include <entropy\ai\entity.h>
#include <entropy\math\math.h>
#include <entropy\math\r2\vector2.h>

namespace entropy
{

//static variable definitions
class SteeringBehaviours;

//vehicle points down the positive x axis in local space
class Vehicle : public Entity
{
public:
	//constructor
	Vehicle();
	Vehicle
	(
		const Point2 &position,
		const Vector2 &front,
		const Vector2 &side,
		const Vector2 &velocity,
		float mass,
		float maxSpeed,
		float maxForce,
		float maxTurnRate
	);
	//methods
	void faceTarget(const Point2 &target);
	virtual void update(float t); //update vehicles position and orientation
	virtual void render(); //render vehicle
	//variables
	//NOTE: have left these public access as this is just
	//a test framework, and i gain nothing from forcing
	//private scope
	Vector2 velocity;				//vehicles velocity
	float mass;						//vehicles mass
	float maxSpeed;					//maximum speed vehicle may travel at
	float maxForce;					//maximum force this vehicle can produce to power itself (think rockets and thrust)
	float maxTurnRate;				//the maximum rate (radians per second) this vehicle can rotate
	SteeringBehaviours *steering;	//steering behaviours
	//vehicle points
	static const Point2 VEHICLE_LOCAL_SPACE_POINTS[3];
	Point2 VEHICLE_WORLD_SPACE_POINTS[3];
	//collision ray
	Ray2 ray;
};

}

#endif
