#ifndef __vector3_h__
#define __vector3_h__

//local dependencies
#include <entropy\cfg.h>

namespace entropy
{

//forward declarations
class Point3;
class Normal3;

class Vector3
{
public:
	//constructors
	Vector3() : x(0.0f),y(0.0f),z(0.0f) {}
	Vector3(float _x,float _y,float _z) : x(_x),y(_y),z(_z) {}
	Vector3(const Point3 &p);
	Vector3(const Normal3 &n);
	Vector3(const Vector3 &right);
	//destructor
	~Vector3() {}
	//operator overloads
	Vector3 &operator=(const Vector3 &v);
	operator float*();
	float &operator[](int i);
	Vector3 operator+(const Vector3 &v) const;
	Vector3 operator+=(const Vector3 &v);
	Vector3 operator-() const;
	Vector3 operator-(const Vector3 &v) const;
	Vector3 operator-=(const Vector3 &v);
	Vector3 operator*(float scalar) const;
	Vector3 &operator*=(float scalar);
	Vector3 operator/(float scalar) const;
	Vector3 &operator/=(float scalar);
	bool operator==(const Vector3 &v) const;
	bool operator!=(const Vector3 &v) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Vector3 &v);
	//methods
	float dot(const Vector3 &v) const;
	float dot(const Normal3 &n) const;
	Vector3 cross(const Vector3 &v) const;
	Vector3 cross(const Normal3 &n) const;
	float length() const;
	float lengthSquared() const;
	void normalize();
	Vector3 perpendicularTo(const Vector3 &v) const;
	Vector3 parallelTo(const Vector3 &v) const;
	//static methods
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Vector3 ZERO;
	static const Vector3 X_AXIS;
	static const Vector3 Y_AXIS;
	static const Vector3 Z_AXIS;
	//variables
	float x,y,z;
private:
	//
protected:
	//
};

}

#endif
