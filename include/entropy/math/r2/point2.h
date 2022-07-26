#ifndef __point2_h__
#define __point2_h__

//local dependencies
#include <entropy\cfg.h>

namespace entropy
{

//forward declarations
class Vector2;

class Point2
{
public:
	//constructors
	Point2() : x(0.0f),y(0.0f) {}
	Point2(float _x,float _y) : x(_x),y(_y) {}
	Point2(const Point2 &right);
	//destructor
	~Point2() {}
	//operator overloads
	Point2 &operator=(const Point2 &p);
	operator float*();
	float &operator[](int i);
	Point2 operator+(const Vector2 &v) const;
	Point2 operator+=(const Vector2 &v);
	Vector2 operator-(const Point2 &p) const;
	Point2 operator-(const Vector2 &v) const;
	Point2 operator-=(const Vector2 &v);
	Point2 operator*(float scalar) const;
	Point2 &operator*=(float scalar);
	Point2 operator/(float scalar) const;
	Point2 &operator/=(float scalar);
	bool operator==(const Point2 &p) const;
	bool operator!=(const Point2 &p) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Point2 &p);
	//methods
	float distance(const Point2 &p) const;
	float distanceSquared(const Point2 &p) const;
	//static methods
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Point2 ZERO;
	static const Point2 X_AXIS;
	static const Point2 Y_AXIS;
	//variables
	float x,y;
private:
	//
protected:
};

}

#endif
