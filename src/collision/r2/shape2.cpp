//local dependencies
#include <entropy\collision\r2\shape2.h>

namespace entropy
{

Shape2::Shape2(const Transform2 &localToWorld)
{
	type = Shape2::NOT_VALID;
	this->localToWorld = localToWorld;
	worldToLocal = localToWorld.inverse();
}

Shape2::Shape2(const Shape2 &right)
{
	type = right.type;
	localToWorld = right.localToWorld;
	worldToLocal = right.worldToLocal;
}

Shape2 &Shape2::operator=(const Shape2 &s)
{
	type = s.type;
	localToWorld = s.localToWorld;
	worldToLocal = s.worldToLocal;
	return *this;
}

}
