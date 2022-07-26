#ifndef __matrix22_h__
#define __matrix22_h__

//local includes
#include <entropy\cfg.h>
#include <entropy\math\angle.h>
#include <entropy\math\r2\point2.h>
#include <entropy\math\r2\vector2.h>
#include <entropy\math\r2\normal2.h>
#include <entropy\math\r2\ray2.h>
#include <entropy\math\r2\line2.h>

namespace entropy
{

//2x2 column major matrix
class Matrix22
{
public:
	//constructors
	Matrix22();
	Matrix22(float m00,float m01,float m10,float m11);
	Matrix22(const Vector2 &basis1,const Vector2 &basis2);
	Matrix22(const Matrix22 &right);
	//destructor
	~Matrix22() {}
	//operator overloads
	Matrix22 &operator=(const Matrix22 &m);
	operator float*();
	float operator()(int r,int c) const;
	float &operator()(int r,int c);
	Matrix22 operator+(const Matrix22 &m) const;
	Matrix22 &operator+=(const Matrix22 &m);
	Matrix22 operator-() const;
	Matrix22 operator-(const Matrix22 &m) const;
	Matrix22 &operator-=(const Matrix22 &m);
	Matrix22 operator*(float scalar) const;
	Point2 operator*(const Point2 &p) const;
	Vector2 operator*(const Vector2 &v) const;
	Normal2 operator*(const Normal2 &n) const;
	Ray2 operator*(const Ray2 &r) const;
	Line2 operator*(const Line2 &l) const;
	Matrix22 operator*(const Matrix22 &m) const;
	Matrix22 &operator*=(float scalar);
	Matrix22 &operator*=(const Matrix22 &m);
	Matrix22 operator/(float scalar) const;
	Matrix22 &operator/=(float scalar);
	bool operator==(const Matrix22 &m) const;
	bool operator!=(const Matrix22 &m) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Matrix22 &m);
	//methods
	void clean();
	float determinant() const;
	Matrix22 transpose() const;
	Matrix22 adjoint() const;
	Matrix22 inverse() const;
	//static methods
	static const Matrix22 rotate(const Angle &angle);
	static const Matrix22 scale(float x,float y);
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Matrix22 ZERO;
	static const Matrix22 IDENTITY;
private:
	//variables
	float M[4];
protected:
	//
};

}

#endif
