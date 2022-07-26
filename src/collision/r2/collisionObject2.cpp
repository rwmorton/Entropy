//local dependencies
#include <entropy\collision\r2\collisionObject2.h>
#include <entropy\util\glUtil.h>
#include <entropy\collision\r2\circle.h>
#include <entropy\collision\r2\box2.h>

namespace entropy
{

CollisionObject2::CollisionObject2(Shape2 *s,const Transform2 *l2w,const Transform2 *w2l)
{
	shape = s;
	localToWorld = l2w;
	worldToLocal = w2l;
}

CollisionObject2::~CollisionObject2()
{
	if(shape)
	{
		delete shape;
	}
}

void CollisionObject2::debugRender(bool worldSpace)
{
	//first check that we have a valid shape
	ASSERT(shape != 0);

	//if worldSpace, transform shape to the world space
	//before rendering
	if(worldSpace)
	{
		switch(shape->getType())
		{
			case Shape2::CIRCLE:
			{
				GlUtil::drawCircle
				(
					(*localToWorld)(Point2::ZERO), /*((Circle *)shape)->getCenter()*/
					((Circle *)shape)->getRadius(),
					32,1.0f,Color::RED
				);
				break;
			}
			case Shape2::BOX:
			{
				//draw box
				GlUtil::drawBox
				(
					(*localToWorld)(((Box2 *)shape)->getMin()),
					(*localToWorld)(((Box2 *)shape)->getMax()),
					1.0f,Color::GREEN
				);
				break;
			}
			case Shape2::TRIANGLE:
			{
				//draw triangle
				break;
			}
			case Shape2::CONVEX:
			{
				//draw convex
				break;
			}
			default: return; //do nothing
		}
	}
	else
	{
		//local space, just render shape
		switch(shape->getType())
		{
			case Shape2::CIRCLE:
			{
				GlUtil::drawCircle
				(
					Point2::ZERO, /*((Circle *)shape)->getCenter()*/
					((Circle *)shape)->getRadius(),
					32,1.0f,Color::RED
				);
				break;
			}
			case Shape2::BOX:
			{
				//draw box
				GlUtil::drawBox
				(
					((Box2 *)shape)->getMin(),
					((Box2 *)shape)->getMax(),
					1.0f,Color::GREEN
				);
				break;
			}
			case Shape2::TRIANGLE:
			{
				//draw triangle
				break;
			}
			case Shape2::CONVEX:
			{
				//draw convex
				break;
			}
			default: return; //do nothing
		}
	}
}

}
