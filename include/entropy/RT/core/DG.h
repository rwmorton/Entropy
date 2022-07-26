#ifndef __DG_h__
#define __DG_h__

//local dependencies
#include <entropy\math\r3\point3.h>
#include <entropy\math\r3\vector3.h>
#include <entropy\math\r3\normal3.h>

namespace entropy
{

//forward declarations
class Shape;

//differential geometry
struct DG
{
	//constructors
	DG();
	DG
	(
		const Point3 &p,
		const Vector3 &dpdu,const Vector3 &dpdv,
		const Vector3 &dndu,const Vector3 &dndv,
		float u,float v,const Shape *shape
	);
	//methods
	void debug() const;
	//variables
	DG(const DG &right);
	Point3 p;				//hit point
	Normal3 nn;				//normalized normal
	Vector3 dpdu,dpdv;		//parametric partial derivatives
	Vector3 dndu,dndv;		//partial derivatives of change in surface normal
	float u,v;				//surface parameters
	const Shape *shape;
};

}

#endif
