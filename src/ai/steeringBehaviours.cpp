//local dependencies
#include <entropy\ai\steeringBehaviours.h>
#include <entropy\ai\vehicle.h>
#include <entropy\math\math.h>
#include <entropy\math\r2\matrix22.h>

namespace entropy
{

SteeringBehaviours::SteeringBehaviours(Vehicle *agent)
{
	vehicle = agent;
	target = targetAgent1 = targetAgent2 = 0;
	steeringForce = Vector2::ZERO;
	deceleration = 0.0f;
	//wander
	wanderRadius = 1.0f;
	wanderDistance = 1.0f;
	wanderJitter = 0.5f;
	//weights
	evadeDistance = 1.0f;
	seekWeight = 1.0f;
	fleeWeight = 1.0f;
	arriveWeight = 1.0f;
	pursuitWeight = 1.0f;
	evadeWeight = 1.0f;
	wanderWeight = 1.0f;
}

void SteeringBehaviours::seek()
{
	Vector2 desiredVelocity = (*target) - vehicle->position;
	if(!Math::isZero(desiredVelocity.lengthSquared()))
	{
		desiredVelocity.normalize();
		desiredVelocity *= vehicle->maxSpeed;
	}
	steeringForce += (desiredVelocity - vehicle->velocity) * seekWeight;
}

void SteeringBehaviours::flee()
{
	Vector2 desiredVelocity = vehicle->position - (*target);
	if(!Math::isZero(desiredVelocity.lengthSquared()))
	{
		desiredVelocity.normalize();
		desiredVelocity *= vehicle->maxSpeed;
	}
	steeringForce += (desiredVelocity - vehicle->velocity) * fleeWeight;
}

void SteeringBehaviours::arrive()
{
	Vector2 toTarget = (*target) - vehicle->position;

	//distance to target
	float dist = toTarget.length();

	if(dist > 0.0f)
	{
		//calculate the speed required to reach the
		//target given the desired decceleration
		float speed = dist / deceleration;

		//make sure the velocity does not exceed the max
		speed = Math::min(speed,vehicle->maxSpeed);

		//from here just proceed like seek, except we don't need to normalize
		//the toTarget vector because we have already gone to the trouble
		//of calculating its length
		Vector2 desiredVelocity = toTarget * (speed / dist);

		steeringForce += (desiredVelocity - vehicle->velocity) * arriveWeight;
	}
}

void SteeringBehaviours::pursuit(const Vehicle *evader)
{
	//if the evader is ahead and facing the agent then
	//we can just seek for the evaders current position
	Vector2 toEvader = evader->position - vehicle->position;

	float relativeHeading = vehicle->velocity.dot(evader->velocity);

	if(toEvader.dot(vehicle->velocity) > 0 && relativeHeading < -0.95)
	{
		//we seek
		if(!Math::isZero(toEvader.lengthSquared()))
		{
			toEvader.normalize();
			toEvader *= vehicle->maxSpeed;
		}
		steeringForce += (toEvader - vehicle->velocity);
	}
	else
	{
		//predict where the evader will be
		//the lookahead time is proportional to the distance
		//between the evader and the pursuer; and is inversely
		//proportional to the sum of the agents velocities
		float lookAheadTime = toEvader.length() / (vehicle->maxSpeed + evader->maxSpeed);

		//now seek to the predicted future positions of the evader
		Point2 tgt = evader->position + evader->velocity * lookAheadTime;

		Vector2 desiredVelocity = tgt - vehicle->position;

		if(!Math::isZero(desiredVelocity.lengthSquared()))
		{
			desiredVelocity.normalize();
			desiredVelocity *= vehicle->maxSpeed;
		}
		steeringForce += (desiredVelocity - vehicle->velocity) * pursuitWeight;
	}
}

void SteeringBehaviours::evade(const Vehicle *pursuer)
{
	Vector2 toPursuer = pursuer->position - vehicle->position;

	//we only flee if we are within the evade distance constant
	if(toPursuer.lengthSquared() < evadeDistance*evadeDistance)
	{
		//the lookahead time is proportional to the distance between
		//the pursuer and the evader; and is inversely proportional
		//to the sum of the agents velocities
		float lookAheadTime = toPursuer.length() / (vehicle->maxSpeed + pursuer->maxSpeed);

		//now flee
		Point2 tgt = pursuer->position + pursuer->velocity * lookAheadTime;

		Vector2 desiredVelocity = vehicle->position - tgt;

		if(!Math::isZero(desiredVelocity.lengthSquared()))
		{
			desiredVelocity.normalize();
			desiredVelocity *= vehicle->maxSpeed;
		}
		steeringForce += (desiredVelocity - vehicle->velocity) * evadeWeight;
	}
}

void SteeringBehaviours::wander()
{
	//add a random vector to our wander direction
	wanderDirection += Vector2(Math::randomBinomial() * wanderJitter,Math::randomBinomial() * wanderJitter);	

	//project this onto our wander circle
	wanderDirection.normalize();
	wanderDirection *= wanderRadius;

	//offset it wanderDistance units in local space
	wanderTarget = Point2(wanderDistance,0.0f) + wanderDirection;

	//transform to world space
	wanderTarget = vehicle->localToWorld(wanderTarget);

	//now seek towards this point
	Vector2 desiredVelocity = wanderTarget - vehicle->position;
	if(!Math::isZero(desiredVelocity.lengthSquared()))
	{
		desiredVelocity.normalize();
		desiredVelocity *= vehicle->maxSpeed;
	}
	steeringForce += (desiredVelocity - vehicle->velocity) * wanderWeight;
}

void SteeringBehaviours::obstacleAvoidance(std::vector<Entity> &obstacles)
{
	std::vector<Entity> collisions;
	std::vector<Entity>::iterator i = obstacles.begin();
	Intersection2 isct;
	while(i != obstacles.end())
	{
		//transform ray to world space for bound intersection testing
		Ray2 r(vehicle->localToWorld(Ray2(Point2::ZERO,Vector2::X_AXIS)));
		if(i->bound.intersect(r,isct))
		{
			collisions.push_back(*i);
			i->color = Color::RED;
		}
		else
		{
			i->color = Color::BLACK;
		}

		i++; //next obstacle
	}

	//get closest entity
	Entity nearest;
	float dist = Math::MAX;
	for(unsigned int x=0; x<collisions.size(); x++)
	{
		//compute distance
		if(vehicle->position.distance(collisions[x].bound.getCenter()) < dist)
		{
			dist = vehicle->position.distance(collisions[x].bound.getCenter());
			nearest = collisions[x];
		}
	}

	//apply steering
	//recompute interesction info
	//transform ray to world space for bound intersection testing
	Ray2 r(vehicle->localToWorld(Ray2(Point2::ZERO,Vector2::X_AXIS)));
	if(nearest.bound.intersect(r,isct))
	{
		//add the normal - this is our lateral force
		Vector2 nn(isct.nn.x,isct.nn.y);

		float d = vehicle->position.distance(isct.p);
		//d += vehicle->bound.getRadius() * vehicle->bound.getRadius();

		float lateralRamp = vehicle->maxSpeed / d;
		//float brake = d / vehicle->maxSpeed;

		//Vector2 newDir = nn + isct.nn.tangent();
		//newDir.normalize();

		steeringForce += nn * lateralRamp; //(newDir * lateralRamp);// + (Vector2::X_AXIS * brake);
		//steeringForce += vehicle->velocity * -brake;
	}
	else
	{
		return; //no force
	}
}

Vector2 SteeringBehaviours::getSteering()
{
	Vector2 ret = steeringForce;
	steeringForce = Vector2::ZERO;
	return ret;
}

}
