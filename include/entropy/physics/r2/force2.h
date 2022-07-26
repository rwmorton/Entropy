#ifndef __force2_h__
#define __force2_h__

//local dependencies
#include <entropy\physics\r2\dynamicObject2.h>

namespace entropy
{

//abstract base class for 2 dimensional force generation
class Force2
{
public:
	//methods
	virtual void updateForce(DynamicObject2 &obj,float t) = 0;
protected:
	/*
	//
	//to create later, force field
	//
	//variables
	Point2 position;		//position of force field
	float magnitude;		//magnitude of the force generated
	Vector2 direction;		//direction of force
	float attenuation;		//attenuation factor based on distance from field position
	*/
};

//2d gravity
class Gravity2 : public Force2
{
public:
	//constructor
	Gravity2(const Vector2 &g=Vector2(0.0f,-9.8f)) : gravity(g) {}
	//methods
	virtual void updateForce(DynamicObject2 &obj,float t);
private:
	//variables
	Vector2 gravity;
};

//2d drag
class Drag2 : public Force2
{
public:
	//constructor
	Drag2(float k1,float k2) : k1(k1),k2(k2) {}
	//methods
	virtual void updateForce(DynamicObject2 &obj,float t);
private:
	//variables
	float k1,k2;	//drag coefficients
};

class Newton2 : public Force2
{
public:
	//constructor
	Newton2(float mag,const Vector2 &dir) : magnitude(mag),direction(dir) { direction.normalize(); }
	//methods
	virtual void updateForce(DynamicObject2 &obj,float t);
private:
	//variables
	float magnitude;
	Vector2 direction;
};

}

#endif
