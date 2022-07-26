#ifndef __line3_h__
#define __line3_h__

//local dependencies
#include <entropy\math\r3\point3.h>
#include <entropy\math\r3\vector3.h>

namespace entropy
{

//forward declarations - for friend classes
class Matrix33;
class Matrix44;
class Transform3;

class Line3
{
public:
	//friend classes - prevent function call overhead
	friend Matrix33;
	friend Matrix44;
	friend Transform3;
	//constructors
	Line3() {}
	Line3(const Point3 &p1,const Point3 &p2);
	Line3(const Point3 &p,const Vector3 &d);
	Line3(const Line3 &right);
	//destructor
	~Line3() {}
	//operator overloads
	Line3 &operator=(const Line3 &l);
	Point3 operator()(float t) const;
	//methods
	float distance(const Point3 &p) const;
	//variables
	Point3 p;
	Vector3 d;
private:
	//
protected:
	//
};

}

#endif
