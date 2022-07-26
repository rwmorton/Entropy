#ifndef __ray2_h__
#define __ray2_h__

//local dependencies
#include <entropy\math\r2\point2.h>
#include <entropy\math\r2\vector2.h>

namespace entropy
{

//forward declarations - for friend classes
class Matrix22;
class Transform2;
class Intersector2;
class Circle;

class Ray2
{
public:
	//friend classes - prevent function call overhead
	friend Matrix22;
	friend Transform2;
	friend Intersector2;
	friend Circle;
	//constructors
	Ray2();
	Ray2(const Point2 &origin,const Vector2 &direction);
	Ray2(const Ray2 &right);
	//destructor
	~Ray2() {}
	//operator overloads
	Ray2 &operator=(const Ray2 &r);
	Point2 operator()(float t) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Ray2 &r);
	//methods
	Point2 getOrigin() const;
	void setOrigin(const Point2 &origin);
	Vector2 getDirection() const;
	void setDirection(const Vector2 &direction);
private:
	//variables
	Point2 o; //ray origin
	Vector2 d; //ray direction
	float mint,maxt,tHit; //intersection depth
protected:
	//
};

}

#endif
