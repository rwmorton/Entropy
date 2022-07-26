//local dependencies
#include <entropy\collision\r2\circle.h>
#include <entropy\math\math.h>

namespace entropy
{

//static variable definitions
const Circle Circle::UNIT(Point2::ZERO,1.0f);

Circle::Circle()
{
	type = Shape2::CIRCLE;
	radius = 1.0f;
}

Circle::Circle(const Point2 &center,float radius)
{
	type = Shape2::CIRCLE;
	this->center = center;
	this->radius = Math::abs(radius);
	localToWorld = Transform2(Matrix22::IDENTITY,Vector2(center.x,center.y));
	worldToLocal = localToWorld.inverse();
}

Circle::Circle(const Circle &right) : Shape2(right)
{
	type = Shape2::CIRCLE;
	center = right.center;
	radius = right.radius;
}

Circle &Circle::operator=(const Circle &c)
{
	type = Shape2::CIRCLE;
	center = c.center;
	radius = c.radius;
	localToWorld = c.localToWorld;
	worldToLocal = c.worldToLocal;
	return *this;
}

std::ostream &operator<<(std::ostream &out,const Circle &c)
{
	out << c.center << ' ' << c.radius;
	return out;
}

Point2 Circle::getCenter() const
{
	return center;
}

void Circle::setCenter(const Point2 &center)
{
	this->center = center;
}

float Circle::getRadius() const
{
	return radius;
}

void Circle::setRadius(float radius)
{
	this->radius = radius;
}

//local space intersection
bool Circle::intersect(const Ray2 &ray,Intersection2 &intersection) const
{
	//transform ray into the circle's local space
	Ray2 r = worldToLocal(ray);

	float a = r.d.dot(r.d);
	float b = 2.0f * (r.o.x*r.d.x + r.o.y*r.d.y);
	float c = (r.o.x*r.o.x + r.o.y*r.o.y) - radius*radius;

	float t0,t1; //roots
	int quadratic = Math::quadratic(a,b,c,&t0,&t1);

	//fill in our intersection structure
	//and return a boolean indicating
	//whether we got an intersection or not
	if(quadratic == Math::NO_ROOTS)
	{
		return false;
	}
	else
	{
		//find parameter along ray segment
		if(t0 > r.maxt || t1 < r.mint)
		{
			return false;
		}
		float tHit = t0;
		if(t0 < r.mint)
		{
			if(t1 > r.maxt)
			{
				return false;
			}
			tHit = t1;
		}

		Point2 p = r(tHit);
		intersection.p = p;
		intersection.nn = Normal2(p.x,p.y);
		intersection.nn.normalize();
		intersection.t = intersection.nn.tangent();
	}

	//remember the intersection data is in
	//local space, so we need to transform
	//it into world space
	intersection.p = localToWorld(intersection.p);
	intersection.nn = localToWorld(intersection.nn);
	intersection.t = localToWorld(intersection.t);

	return true;
}

#ifdef DEBUG
void Circle::test()
{
	std::cout << "Circle test" << std::endl;

	Circle c(Point2(1,2),2.0f);
	//Ray2 r(Point2(4,4),Vector2(-1,-1));
	Ray2 r(Point2(5,0),-Vector2::X_AXIS);
	Intersection2 i;

	std::cout << "Circle: " << c << std::endl;
	std::cout << "Ray: " << r << std::endl;

	//transform ray into local space
	std::cout << "Ray from world to local space: " << c.worldToLocal(r) << std::endl;

	//test intersection
	if(c.intersect(r,i))
	{
		std::cout << "got an intersection (in world space)" << std::endl;
		std::cout << "intersection point: " << i.p << std::endl;
	}
	else
	{
		std::cout << "did not get an intersection" << std::endl;
	}

	std::cout << std::endl;
}
#endif

}
