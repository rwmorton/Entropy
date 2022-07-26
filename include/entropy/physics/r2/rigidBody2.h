//local dependencies
#include <entropy\physics\r2\dynamicObject2.h>

namespace entropy
{

class RigidBody2 : public DynamicObject2
{
public:
	//methods
	virtual Transform2 getWorldTransform() const;
	virtual void integrate(float t);
	#ifdef DEBUG
	virtual void debugRender();
	#endif
private:
	//
protected:
	//variables
	float angularVelocity;		//angular velocity of this body
};

}
