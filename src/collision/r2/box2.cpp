//local dependencies
#include <entropy\collision\r2\box2.h>
#include <entropy\math\math.h>
#include <entropy\util\algo.h>

namespace entropy
{

//static variable definitions
const Box2 Box2::UNIT
(
	Point2(-0.5f,-0.5f),
	Point2(0.5f,0.5f)
);

Box2::Box2()
{
	type = Shape2::BOX;
	min = Point2(-0.5f,-0.5f);
	max = Point2(0.5f,0.5f);
}

Box2::Box2(const Point2 &min,const Point2 &max)
{
	type = Shape2::BOX;
	this->min = min;
	this->max = max;

	//make sure min is the smaller corner than max
	//only need to check one coordinate
	//
	//if a box with no width/height is passed then
	//thats it, no check is made for this condition
	//will enforce a check if required
	if(this->min.x > this->max.x)
	{
		Algo::swap<Point2>(this->min,this->max);
	}

	//transforms default to identity
}

Box2::Box2(const Box2 &right) : Shape2(right)
{
	type = Shape2::BOX;
	min = right.min;
	max = right.max;
	//transforms copied in shape2 constructor call
}

Box2 &Box2::operator=(const Box2 &b)
{
	type = Shape2::BOX;
	min = b.min;
	max = b.max;
	//copy transforms explicitly - shape2 assignment operator ?
	localToWorld = b.localToWorld;
	worldToLocal = b.worldToLocal;
	return *this;
}

std::ostream &operator<<(std::ostream &out,const Box2 &b)
{
	out << b.min << ' ' << b.max;
	return out;
}

Point2 Box2::getMin() const
{
	return min;
}

void Box2::setMin(const Point2 &min)
{
	this->min = min;
}

Point2 Box2::getMax() const
{
	return max;
}

void Box2::setMax(const Point2 &max)
{
	this->max = max;
}

//local space intersection
bool Box2::intersect(const Ray2 &ray,Intersection2 &intersection) const
{
	return false;
}

#ifdef DEBUG
void Box2::test()
{
	std::cout << "Box2 test" << std::endl;
	std::cout << std::endl;
}
#endif

}
