//local dependencies
#include <entropy\RT\core\shape.h>

namespace entropy
{

Shape::Shape(const Transform3 &l2w,bool ro) : ReverseOrientation(ro),TransformSwapsHandedness(l2w.swapsHandedness())
{
	LocalToWorld = l2w;
	WorldToLocal = l2w.inverse();
}

BBox3 Shape::worldBound() const
{
	return LocalToWorld(localBound());
}

bool Shape::canIntersect() const
{
	return true;
}

void Shape::refine(std::vector<Shape> &refined) const
{
	//TODO error stuff
	//ie. unimplemented refine method blah blah
}

void Shape::getShadingGeometry(const Transform3 &l2w,const DG &dg,DG &dgShading) const
{
	dgShading = dg;
}

}
