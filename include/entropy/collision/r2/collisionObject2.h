#ifndef __collisionObject_h__
#define __collisionObject_h__

//local dependencies
#include <entropy\collision\r2\shape2.h>
#include <entropy\math\r2\transform2.h>

namespace entropy
{

//takes a pointer to a shape and takes ownership of
//the shape. this means it has to manage the shapes
//heap memory.
//
//also takes pointers to local-to-world and
//world-to-local transforms.
//
//for this reason we cannot make copies
class CollisionObject2
{
public:
	//constructors
	CollisionObject2(Shape2 *s,const Transform2 *l2w,const Transform2 *w2l);
	//destructor
	~CollisionObject2();
	//operator overloads
	//friend operators
	//methods
	void debugRender(bool worldSpace=true);
private:
	//prevent copies
	CollisionObject2(const CollisionObject2 &);
	CollisionObject2 &operator=(const CollisionObject2 &);
	//variables
	Shape2 *shape;
	const Transform2 *localToWorld;
	const Transform2 *worldToLocal;
protected:
	//
};

}

#endif
