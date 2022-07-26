//local dependencies
#include <entropy\collision\r2\intersector2.h>
#include <entropy\math\math.h>

namespace entropy
{

bool Intersector2::intersect(const CollisionObject2 &co1,const CollisionObject2 &co2,Contact2 &c)
{
	return false;
}

bool Intersector2::intersectP(const CollisionObject2 &co1,const CollisionObject2 &co2)
{
	return false;
}

bool Intersector2::intersect(const Ray2 &r,const Circle &circle,Intersection2 &i)
{
	float radius = circle.getRadius();
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
		i.p = p;
		i.nn = Normal2(p.x,p.y);
		i.nn.normalize();
		i.t = i.nn.tangent();
	}

	return true;
}

bool Intersector2::intersectP(const Ray2 &r,const Circle &circle)
{
	float radius = circle.getRadius();
	float a = r.d.dot(r.d);
	float b = 2.0f * (r.o.x*r.d.x + r.o.y*r.d.y);
	float c = (r.o.x*r.o.x + r.o.y*r.o.y) - radius*radius;

	float t0,t1; //roots
	int quadratic = Math::quadratic(a,b,c,&t0,&t1);

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
		if(t0 < r.mint)
		{
			if(t1 > r.maxt)
			{
				return false;
			}
		}
	}

	return true;
}

bool Intersector2::intersect(const Circle &c1,const Circle &c2,Contact2 &c)
{
	float dist = c1.getCenter().distanceSquared(c2.getCenter());
	float radiusSum = c1.getRadius() + c2.getRadius();

	if(dist <= radiusSum*radiusSum)
	{
		dist = Math::sqrt(dist);
		c.nn = Normal2(c2.getCenter() - c1.getCenter());
		c.t = c.nn.tangent();
		c.p = c1.getCenter() + (c.nn * dist);
		c.depth = dist;

		return true;
	}

	return false;
}

bool Intersector2::intersectP(const Circle &c1,const Circle &c2)
{
	float dist = c1.getCenter().distanceSquared(c2.getCenter());
	float radiusSum = c1.getRadius() + c2.getRadius();
	return dist <= radiusSum*radiusSum;
}

}
