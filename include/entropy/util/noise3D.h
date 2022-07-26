#ifndef __noise3D_h__
#define __noise3D_h__

//local dependencies
#include <entropy\math\r3\vector3.h>

namespace entropy
{

class Noise3D
{
public:
	//constructor
	Noise3D();
	//methods
	float noise(const Vector3 &p) const;
	float turbulence(const Vector3 &p,int depth) const;
	float dturbulence(const Vector3 &p,int depth,float d) const;
	float omega(float t) const;
	Vector3 gamma(int i,int j,int k) const;
	int intGamma(int i,int j) const;
	float knot(int i,int j,int k,Vector3 &v) const;
private:
	//static variables
	static const Vector3 grad[16];
	//variables
	int phi[16];
protected:
	//
};

}

#endif
