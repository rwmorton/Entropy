#ifndef __particle2_h__
#define __particle2_h__

//local dependencies
#include <entropy\physics\r2\dynamicObject2.h>

namespace entropy
{

class Particle2 : public DynamicObject2
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
	//
};

}

#endif
