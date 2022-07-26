#ifndef __box2_h__
#define __box2_h__

//local dependencies
#include <entropy\collision\r2\shape2.h>
#include <entropy\cfg.h>
#include <entropy\math\r2\point2.h>

namespace entropy
{

class Box2 : public Shape2
{
public:
	//constructors
	Box2();
	Box2(const Point2 &min,const Point2 &max);
	Box2(const Box2 &right);
	//destructor
	~Box2() {}
	//operator overloads
	Box2 &operator=(const Box2 &b);
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Box2 &b);
	//methods
	Point2 getMin() const;
	void setMin(const Point2 &min);
	Point2 getMax() const;
	void setMax(const Point2 &max);
	virtual bool intersect(const Ray2 &ray,Intersection2 &intersection) const;
	//static methods
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Box2 UNIT;
private:
	//variables
	Point2 min;
	Point2 max;
protected:
	//
};

}

#endif
