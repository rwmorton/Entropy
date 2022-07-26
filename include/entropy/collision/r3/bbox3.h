#ifndef __bbox3_h__
#define __bbox3_h__

//local dependencies
#include <entropy\math\r3\point3.h>

namespace entropy
{

class BBox3
{
public:
	//constructor
	BBox3();
	BBox3(const Point3 &min,const Point3 &max);
	//destructor
	~BBox3() {}
	//operator overloads
private:
	//variables
	Point3 min;
	Point3 max;
protected:
	//
};

}

#endif
