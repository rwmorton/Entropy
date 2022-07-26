#ifndef __intersection_h__
#define __intersection_h__

//local dependencies
#include <entropy\RT\core\DG.h>
#include <entropy\math\r3\transform3.h>

namespace entropy
{

struct Intersection
{
	//Intersection() { primitive = 0; }
	//BSDF *getBSDF(const RayDifferential &ray) const;
	//Spectrum Le(const Vector3 &wo) const;
	DG dg;
	//const Primitive *primitive;
	Transform3 WorldToObject;
};

}

#endif
