#ifndef __circle_h__
#define __circle_h__

//local dependencies
#include <entropy\collision\r2\shape2.h>
#include <entropy\cfg.h>
#include <entropy\math\r2\point2.h>

namespace entropy
{

class Circle : public Shape2
{
public:
	//constructors
	Circle();
	Circle(const Point2 &center,float radius);
	Circle(const Circle &right);
	//destructor
	~Circle() {}
	//operator overloads
	Circle &operator=(const Circle &c);
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Circle &c);
	//methods
	Point2 getCenter() const;
	void setCenter(const Point2 &center);
	float getRadius() const;
	void setRadius(float radius);
	virtual bool intersect(const Ray2 &ray,Intersection2 &intersection) const;
	//static methods
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Circle UNIT;
private:
	//variables
	Point2 center;
	float radius;
protected:
	//
};

}

#endif
