#ifndef __ray3_h__
#define __ray3_h__

//local dependencies
#include <entropy\math\r3\point3.h>
#include <entropy\math\r3\vector3.h>

namespace entropy
{

//forward declarations - for friend classes
class Matrix33;
class Matrix44;
class Transform3;

class Ray3
{
public:
	//friend classes - prevent function call overhead
	friend Matrix33;
	friend Matrix44;
	friend Transform3;
	//constructors
	Ray3();
	Ray3(const Point3 &origin,const Vector3 &direction);
	Ray3(const Ray3 &right);
	//destructor
	~Ray3() {}
	//operator overloads
	Ray3 &operator=(const Ray3 &r);
	Point3 operator()(float t) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Ray3 &r);
	//methods
	Point3 getOrigin() const;
	void setOrigin(const Point3 &origin);
	Vector3 getDirection() const;
	void setDirection(const Vector3 &direction);
	//variables
	Point3 o;			//ray origin
	Vector3 d;			//ray direction
	float mint,maxt;	//ray segment
	float tHit;			//intersection depth
private:
	//
protected:
	//
};

}

#endif
