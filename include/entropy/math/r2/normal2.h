#ifndef __normal2_h__
#define __normal2_h__

//local dependencies
#include <entropy\cfg.h>

namespace entropy
{

//forward declarations
class Vector2;

class Normal2
{
public:
	//constructors
	Normal2() : x(0.0f),y(0.0f) {}
	Normal2(float _x,float _y) : x(_x),y(_y) {}
	Normal2(const Vector2 &v);
	Normal2(const Normal2 &right);
	//destructor
	~Normal2() {}
	//operator overloads
	Normal2 &operator=(const Normal2 &n);
	operator float*();
	float &operator[](int i);
	Normal2 operator+(const Normal2 &n) const;
	Normal2 operator+=(const Normal2 &n);
	Normal2 operator-() const;
	Normal2 operator-(const Normal2 &n) const;
	Normal2 operator-=(const Normal2 &n);
	Normal2 operator*(float scalar) const;
	Normal2 &operator*=(float scalar);
	Normal2 operator/(float scalar) const;
	Normal2 &operator/=(float scalar);
	bool operator==(const Normal2 &n) const;
	bool operator!=(const Normal2 &n) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Normal2 &n);
	//methods
	float dot(const Normal2 &n) const;
	float dot(const Vector2 &v) const;
	float length() const;
	float lengthSquared() const;
	void normalize();
	Vector2 tangent() const;
	//static methods
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Normal2 ZERO;
	static const Normal2 X_AXIS;
	static const Normal2 Y_AXIS;
	//variables
	float x,y;
private:
	//
protected:
	//
};

}

#endif
