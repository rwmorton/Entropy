#ifndef __line2_h__
#define __line2_h__

//local dependencies
#include <entropy\math\r2\point2.h>
#include <entropy\math\r2\vector2.h>

namespace entropy
{

//forward declarations - for friend classes
class Matrix22;
class Transform2;

class Line2
{
public:
	//friend classes - prevent function call overhead
	friend Matrix22;
	friend Transform2;
	//constructors
	Line2() {}
	Line2(const Point2 &p1,const Point2 &p2);
	Line2(const Point2 &p,const Vector2 &d);
	Line2(const Line2 &right);
	//destructor
	~Line2() {}
	//operator overloads
	Line2 &operator=(const Line2 &l);
	Point2 operator()(float t) const;
	//methods
	float distance(const Point2 &p) const;
private:
	//variables
	Point2 p;
	Vector2 d;
protected:
	//
};

}

#endif
