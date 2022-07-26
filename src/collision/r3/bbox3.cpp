//local dependencies
#include <entropy\collision\r3\bbox3.h>
#include <entropy\math\math.h>

namespace entropy
{

BBox3::BBox3() : min(Math::MAX,Math::MAX,Math::MAX),max(Math::MIN,Math::MIN,Math::MIN)
{
}

BBox3::BBox3(const Point3 &min,const Point3 &max) : min(min),max(max) {}

}
