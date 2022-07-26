#ifndef __matrix33_h__
#define __matrix33_h__

//local includes
#include <entropy\cfg.h>
#include <entropy\math\angle.h>
#include <entropy\math\r3\point3.h>
#include <entropy\math\r3\vector3.h>
#include <entropy\math\r3\normal3.h>
#include <entropy\math\r3\ray3.h>
#include <entropy\math\r3\line3.h>
#include <entropy\collision\r3\bbox3.h>

namespace entropy
{

//3x3 column major matrix
class Matrix33
{
public:
	//constructors
	Matrix33();
	Matrix33
	(
		float m00,float m01,float m02,
		float m10,float m11,float m12,
		float m20,float m21,float m22
	);
	Matrix33(const Vector3 &basis1,const Vector3 &basis2,const Vector3 &basis3);
	Matrix33(const Matrix33 &right);
	//destructor
	~Matrix33() {}
	//operator overloads
	Matrix33 &operator=(const Matrix33 &m);
	operator float*();
	float operator()(int r,int c) const;
	float &operator()(int r,int c);
	Matrix33 operator+(const Matrix33 &m) const;
	Matrix33 &operator+=(const Matrix33 &m);
	Matrix33 operator-() const;
	Matrix33 operator-(const Matrix33 &m) const;
	Matrix33 &operator-=(const Matrix33 &m);
	Matrix33 operator*(float scalar) const;
	Point3 operator*(const Point3 &p) const;
	Vector3 operator*(const Vector3 &v) const;
	Normal3 operator*(const Normal3 &n) const;
	Ray3 operator*(const Ray3 &r) const;
	Line3 operator*(const Line3 &l) const;
	BBox3 operator*(const BBox3 &b) const;
	Matrix33 operator*(const Matrix33 &m) const;
	Matrix33 &operator*=(float scalar);
	Matrix33 &operator*=(const Matrix33 &m);
	Matrix33 operator/(float scalar) const;
	Matrix33 &operator/=(float scalar);
	bool operator==(const Matrix33 &m) const;
	bool operator!=(const Matrix33 &m) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Matrix33 &m);
	//methods
	void clean();
	float determinant() const;
	Matrix33 transpose() const;
	Matrix33 adjoint() const;
	Matrix33 inverse() const;
	//static methods
	static const Matrix33 rotate(const Angle &xAngle,const Angle &yAngle,const Angle &zAngle);
	static const Matrix33 rotateX(const Angle &angle);
	static const Matrix33 rotateY(const Angle &angle);
	static const Matrix33 rotateZ(const Angle &angle);
	static const Matrix33 scale(float x,float y,float z);
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Matrix33 ZERO;
	static const Matrix33 IDENTITY;
private:
	//variables
	float M[9];
protected:
	//
};

}

#endif
