#ifndef __vector2_h__
#define __vector2_h__

//local dependencies
#include <entropy\cfg.h>

namespace entropy
{

//forward declarations
class Point2;
class Normal2;

class Vector2
{
public:
	//constructors
	Vector2() : x(0.0f),y(0.0f) {}
	Vector2(float _x,float _y) : x(_x),y(_y) {}
	Vector2(const Point2 &p);
	Vector2(const Normal2 &n);
	Vector2(const Vector2 &right);
	//destructor
	~Vector2() {}
	//operator overloads
	Vector2 &operator=(const Vector2 &v);
	operator float*();
	float &operator[](int i);
	Vector2 operator+(const Vector2 &v) const;
	Vector2 operator+=(const Vector2 &v);
	Vector2 operator-() const;
	Vector2 operator-(const Vector2 &v) const;
	Vector2 operator-=(const Vector2 &v);
	Vector2 operator*(float scalar) const;
	Vector2 &operator*=(float scalar);
	Vector2 operator/(float scalar) const;
	Vector2 &operator/=(float scalar);
	bool operator==(const Vector2 &v) const;
	bool operator!=(const Vector2 &v) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Vector2 &v);
	//methods
	float dot(const Vector2 &v) const;
	float dot(const Normal2 &n) const;
	float length() const;
	float lengthSquared() const;
	void normalize();
	Vector2 perpendicular() const;
	Vector2 perpendicularTo(const Vector2 &v) const;
	Vector2 parallelTo(const Vector2 &v) const;
	//static methods
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Vector2 ZERO;
	static const Vector2 X_AXIS;
	static const Vector2 Y_AXIS;
	//variables
	float x,y;
private:
	//
protected:
	//
};

}

#endif
