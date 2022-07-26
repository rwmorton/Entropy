#ifndef __camera_h__
#define __camera_h__

//local dependencies
#include <entropy\cfg.h>
#include <entropy\RT\core\DG.h>
#include <entropy\collision\r3\bbox3.h>
#include <entropy\math\r3\transform3.h>
#include <entropy\math\r3\ray3.h>

namespace entropy
{

//forward declarations
struct DG;

class Shape
{
public:
	//constructor
	Shape(const Transform3 &l2w,bool reverseOrientation=false);
	//destructor
	virtual ~Shape() {}
	//methods
	virtual BBox3 localBound() const = 0;
	virtual BBox3 worldBound() const;
	virtual bool canIntersect() const;
	virtual void refine(std::vector<Shape> &refined) const;
	virtual bool intersect(const Ray3 &ray,float *tHit,DG &dg) const = 0;
	virtual bool intersectP(const Ray3 &ray) const = 0;
	virtual void getShadingGeometry(const Transform3 &l2w,const DG &dg,DG &dgShading) const;
	virtual float area() const = 0;
	virtual void debug() const = 0;
	//variables
	Transform3 LocalToWorld;
	Transform3 WorldToLocal;
	const bool ReverseOrientation;
	const bool TransformSwapsHandedness;
private:
	//
protected:
	//
};

}

#endif
