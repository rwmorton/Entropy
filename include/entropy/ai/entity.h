#ifndef __entity_h__
#define __entity_h__

//local dependencies
#include <entropy\math\r2\point2.h>
#include <entropy\math\r2\vector2.h>
#include <entropy\math\r2\transform2.h>
#include <entropy\math\math.h>
#include <entropy\collision\r2\circle.h>
#include <entropy\color\color.h>
#include <entropy\util\glutil.h>

namespace entropy
{

class Entity
{
public:
	//constructor
	Entity()
	{
		position = Point2::ZERO;
		front = Vector2::X_AXIS;
		side = Vector2::Y_AXIS;
		//transforms default to the identity
		//circle defaults to a unit circle at the origin
		color = Color::BLUE;
	}
	Entity(const Circle &b,const Color &c=Color::BLACK)
	{
		position = Point2::ZERO;
		front = Vector2::X_AXIS;
		side = Vector2::Y_AXIS;
		//transforms default to the identity
		bound = b;
		color = c;
	}
	//methods
	virtual void update()
	{
		localToWorld = (Transform2::rotate(Angle(Math::aTan2(front.y,front.x))))(Transform2::translate(Vector2(position.x,position.y)));
		worldToLocal = localToWorld.inverse();
	}
	virtual void render()
	{
		#ifdef DEBUG
		//draw entity bounds
		GlUtil::drawCircle(localToWorld(bound.getCenter()),bound.getRadius(),32,1.0f,color);
		//draw front vector
		//GlUtil::drawVector(front,position,3.0f,Color::RED);
		//draw side vector
		//GlUtil::drawVector(side,position,3.0f,Color::GREEN);
		#endif
	}
	//variables
	Point2 position;		//entities position
	Vector2 front;			//entities front vector
	Vector2 side;			//entities side vector
	//transforms
	Transform2 localToWorld;
	Transform2 worldToLocal;
	//bound
	Circle bound;
	//temp
	Color color;
private:
	//
protected:
	//
};

}

#endif
