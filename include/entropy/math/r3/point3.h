#ifndef __point3_h__
#define __point3_h__

//local dependencies
#include <entropy\cfg.h>

namespace entropy
{

//forward declarations
class Vector3;

class Point3
{
public:
	//constructors
	Point3() : x(0.0f),y(0.0f),z(0.0f) {}
	Point3(float _x,float _y,float _z) : x(_x),y(_y),z(_z) {}
	Point3(const Point3 &right);
	//destructor
	~Point3() {}
	//operator overloads
	Point3 &operator=(const Point3 &p);
	operator float*();
	float &operator[](int i);
	Point3 operator+(const Vector3 &v) const;
	Point3 operator+=(const Vector3 &v);
	Vector3 operator-(const Point3 &p) const;
	Point3 operator-(const Vector3 &v) const;
	Point3 operator-=(const Vector3 &v);
	Point3 operator*(float scalar) const;
	Point3 &operator*=(float scalar);
	Point3 operator/(float scalar) const;
	Point3 &operator/=(float scalar);
	bool operator==(const Point3 &p) const;
	bool operator!=(const Point3 &p) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Point3 &p);
	//methods
	float distance(const Point3 &p) const;
	float distanceSquared(const Point3 &p) const;
	//static methods
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Point3 ZERO;
	static const Point3 X_AXIS;
	static const Point3 Y_AXIS;
	static const Point3 Z_AXIS;
	//variables
	float x,y,z;
private:
	//
protected:
};

}

#endif
