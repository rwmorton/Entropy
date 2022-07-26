#ifndef __normal3_h__
#define __normal3_h__

//local dependencies
#include <entropy\cfg.h>

namespace entropy
{

//forward declarations
class Vector3;

class Normal3
{
public:
	//constructors
	Normal3() : x(0.0f),y(0.0f),z(0.0f) {}
	Normal3(float _x,float _y,float _z) : x(_x),y(_y),z(_z) {}
	Normal3(const Vector3 &v);
	Normal3(const Normal3 &right);
	//destructor
	~Normal3() {}
	//operator overloads
	Normal3 &operator=(const Normal3 &n);
	operator float*();
	float &operator[](int i);
	Normal3 operator+(const Normal3 &n) const;
	Normal3 operator+=(const Normal3 &n);
	Normal3 operator-() const;
	Normal3 operator-(const Normal3 &n) const;
	Normal3 operator-=(const Normal3 &n);
	Normal3 operator*(float scalar) const;
	Normal3 &operator*=(float scalar);
	Normal3 operator/(float scalar) const;
	Normal3 &operator/=(float scalar);
	bool operator==(const Normal3 &n) const;
	bool operator!=(const Normal3 &n) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Normal3 &n);
	//methods
	float dot(const Normal3 &n) const;
	float dot(const Vector3 &n) const;
	Normal3 cross(const Normal3 &n) const;
	Normal3 cross(const Vector3 &v) const;
	float length() const;
	float lengthSquared() const;
	void normalize();
	Normal3 perpendicularTo(const Normal3 &n) const;
	Normal3 parallelTo(const Normal3 &n) const;
	//static methods
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Normal3 ZERO;
	static const Normal3 X_AXIS;
	static const Normal3 Y_AXIS;
	static const Normal3 Z_AXIS;
	//variables
	float x,y,z;
private:
	//
protected:
	//
};

}

#endif
