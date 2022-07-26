//local dependencies
#include <entropy\ai\vehicle.h>
#include <entropy\ai\steeringBehaviours.h>
#include <entropy\math\math.h>
#include <entropy\math\r2\matrix22.h>
#include <entropy\util\glUtil.h>

namespace entropy
{

//static variable definitions
const Point2 Vehicle::VEHICLE_LOCAL_SPACE_POINTS[3] =
{
	Point2(-0.323f,0.323f),
	Point2(-0.323f,-0.323f),
	Point2(0.427f,0.0f)
};

Vehicle::Vehicle() : Entity()
{
	bound.setRadius(0.5f);

	ray = Ray2(Point2::ZERO,Vector2::X_AXIS);
}

Vehicle::Vehicle
(
	const Point2 &position,
	const Vector2 &front,
	const Vector2 &side,
	const Vector2 &velocity,
	float mass,
	float maxSpeed,
	float maxForce,
	float maxTurnRate
)
{
	this->position = position;
	this->front = front;
	this->side = side;
	this->velocity = velocity;
	this->mass = mass;
	this->maxSpeed = maxSpeed;
	this->maxForce = maxForce;
	this->maxTurnRate = maxTurnRate;

	//transforms default to the identity
	bound.setRadius(0.5f);

	ray = Ray2(Point2::ZERO,Vector2::X_AXIS);
}

void Vehicle::faceTarget(const Point2 &target)
{
	front = Vector2::X_AXIS;

	Vector2 toTarget = target - position;
	toTarget.normalize();

	float angle = Math::aCos(front.dot(toTarget));

	//rotate front vector by angle
	//we first need to calculate the sign
	//as aCos returns in a range of [-pi,pi]
	//which is not suitable
	int sign;
	if(front.y*toTarget.x > front.x*toTarget.y)
	{
		sign = -1;
	}
	else
	{
		sign = 1;
	}
	Matrix22 rotation = Matrix22::rotate(Angle(angle * sign));
	front = rotation * front;

	//normalize the front vector
	front.normalize();

	//recompute the side vector
	side = front.perpendicular();
	side.normalize();
}

void Vehicle::update(float t)
{
	//acceleration = force / mass
	Vector2 acceleration = steering->getSteering() / mass;

	//update velocity
	velocity += acceleration * t;

	//make sure vehicle does not exceed maximum velocity
	if(velocity.length() > maxSpeed)
	{
		velocity.normalize();
		velocity *= maxSpeed;
	}

	//update the position
	position += velocity * t;

	//update basis if non-zero velocity
	if(!Math::isZero(velocity.lengthSquared()))
	{
		front = velocity;
		side = front.perpendicular();

		front.normalize();
		side.normalize();
	}

	Entity::update(); //updates transforms
}

void Vehicle::render()
{
	//draw agent
	//first transform its local object vertices into world space
	VEHICLE_WORLD_SPACE_POINTS[0] = localToWorld(VEHICLE_LOCAL_SPACE_POINTS[0]);
	VEHICLE_WORLD_SPACE_POINTS[1] = localToWorld(VEHICLE_LOCAL_SPACE_POINTS[1]);
	VEHICLE_WORLD_SPACE_POINTS[2] = localToWorld(VEHICLE_LOCAL_SPACE_POINTS[2]);
	//now draw it
	GlUtil::drawLineLoop(Transform2::IDENTITY,&VEHICLE_WORLD_SPACE_POINTS[0],3,1.0f,Color::GREEN);

	#ifdef DEBUG
	//draw wander circle (offset)
	//GlUtil::drawCircle(localToWorld(Point2(steering->wanderDistance,0.0f)),steering->wanderRadius,16,1.0f,Color(0.234f,0.134f,0.343f));
	//draw velocity vector
	//GlUtil::drawVector(velocity,position,1.0f,Color::RED);
	//draw wander target
	//GlUtil::drawPoint(steering->wanderTarget,5.0f,Color::RED);
	//draw collision ray
	//GlUtil::drawRay(localToWorld(Ray2(Point2::ZERO,Vector2::X_AXIS)),10.0f);
	#endif

	Entity::render();
}

}
