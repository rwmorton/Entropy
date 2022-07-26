//local dependencies
#include <entropy\RT\core\DG.h>
#include <entropy\RT\core\shape.h>
#include <entropy\util\glUtil.h>

namespace entropy
{

DG::DG() : u(0.0f),v(0.0f),shape(0) {}

DG::DG
(
	const Point3 &p,
	const Vector3 &dpdu,const Vector3 &dpdv,
	const Vector3 &dndu,const Vector3 &dndv,
	float u,float v,const Shape *shape
) : p(p),dpdu(dpdu),dpdv(dpdv),dndu(dndu),dndv(dndv),u(u),v(v),shape(shape)
{
	nn = Normal3(dpdu.cross(dpdv));
	nn.normalize();
	//adjust normal based on orientation and handedness
	if(shape->ReverseOrientation ^ shape->TransformSwapsHandedness)
	{
		nn *= -1.0f;
	}
}

DG::DG(const DG &right)
{
	p = right.p;
	nn = right.nn;
	dpdu = right.dpdu;
	dpdv = right.dpdv;
	dndu = right.dndu;
	dndv = right.dndv;
	u = right.u;
	v = right.v;
	shape = right.shape;
}

void DG::debug() const
{
	GlUtil::drawPoint(p,5.0f,Color::RED);
	GlUtil::drawVector(Vector3(nn.x,nn.y,nn.z),p,2.0f,Color::GREEN);
}

}
