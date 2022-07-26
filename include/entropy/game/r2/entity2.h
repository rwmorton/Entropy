////////////
// NB! really just temp for now

#ifndef __entity2_h__
#define __entity2_h__

//local dependencies
#include <entropy\math\r2\transform2.h>
#include <entropy\collision\r2\collisionObject2.h>
#include <entropy\collision\r2\circle.h>
#include <entropy\collision\r2\box2.h>
#include <entropy\util\glUtil.h>

namespace entropy
{

//this is supposed to be the base class (pure virtual) for all
//game entities (2D), for example, MovingEntity2. im not going
//to enforce that just yet, as I don't require the functionality
//so this just holds for testing purposes only.
class Entity2
{
public:
	//constructor
	Entity2()
	{
		localToWorld = new Transform2;
		worldToLocal = new Transform2;
		entityShape = new Circle;
		collisionObject = new CollisionObject2(new Box2(Point2(-1,-1),Point2(1,1)),localToWorld,worldToLocal);
	}
	//destructor
	~Entity2()
	{
		delete localToWorld;
		delete worldToLocal;
		delete collisionObject;
		delete entityShape;
	}
	//methods
	virtual void update()
	{
		*localToWorld = (Transform2::rotate(Angle(rotationRadians)))(Transform2::translate(Vector2(position.x,position.y)));
		*worldToLocal = localToWorld->inverse();
	}
	virtual void render(bool worldSpace)
	{
		//render collision obj
		collisionObject->debugRender(worldSpace);

		if(worldSpace)
		{
			//render entity shape in world space
			GlUtil::drawCircle((*localToWorld)(Point2::ZERO),((Circle *)entityShape)->getRadius(),32,1.0f,Color::RED);
		}
		else
		{
			//render entity shape in local space
			GlUtil::drawCircle(Point2::ZERO,((Circle *)entityShape)->getRadius(),32,1.0f,Color::RED);
		}
	}
	//
	//VARIABLES!!!! for testing
	//
	float rotationRadians;
	Point2 position;
private:
	//variables
	Transform2 *localToWorld;
	Transform2 *worldToLocal;
	CollisionObject2 *collisionObject;
	Shape2 *entityShape;
protected:
	//
};

}

#endif
