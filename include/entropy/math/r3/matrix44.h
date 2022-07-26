#ifndef __matrix44_h__
#define __matrix44_h__

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

//4x4 column major matrix
class Matrix44
{
public:
	//constructors
	Matrix44();
	Matrix44
	(
		float m00,float m01,float m02,float m03,
		float m10,float m11,float m12,float m13,
		float m20,float m21,float m22,float m23,
		float m30,float m31,float m32,float m33
	);
	Matrix44(const Vector3 &basis1,const Vector3 &basis2,const Vector3 &basis3);
	Matrix44(const Matrix44 &right);
	//destructor
	~Matrix44() {}
	//operator overloads
	Matrix44 &operator=(const Matrix44 &m);
	operator float*();
	float operator()(int r,int c) const;
	float &operator()(int r,int c);
	Matrix44 operator+(const Matrix44 &m) const;
	Matrix44 &operator+=(const Matrix44 &m);
	Matrix44 operator-() const;
	Matrix44 operator-(const Matrix44 &m) const;
	Matrix44 &operator-=(const Matrix44 &m);
	Matrix44 operator*(float scalar) const;
	Point3 operator*(const Point3 &p) const;
	Vector3 operator*(const Vector3 &v) const;
	Normal3 operator*(const Normal3 &n) const;
	Ray3 operator*(const Ray3 &r) const;
	Line3 operator*(const Line3 &l) const;
	BBox3 operator*(const BBox3 &b) const;
	Matrix44 operator*(const Matrix44 &m) const;
	Matrix44 &operator*=(float scalar);
	Matrix44 &operator*=(const Matrix44 &m);
	Matrix44 operator/(float scalar) const;
	Matrix44 &operator/=(float scalar);
	bool operator==(const Matrix44 &m) const;
	bool operator!=(const Matrix44 &m) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Matrix44 &m);
	//methods
	void clean();
	float determinant() const;
	Matrix44 transpose() const;
	Matrix44 adjoint() const;
	Matrix44 inverse() const;
	//static methods
	static const Matrix44 rotate(const Angle &xAngle,const Angle &yAngle,const Angle &zAngle);
	static const Matrix44 rotateX(const Angle &angle);
	static const Matrix44 rotateY(const Angle &angle);
	static const Matrix44 rotateZ(const Angle &angle);
	static const Matrix44 translate(float x,float y,float z);
	static const Matrix44 scale(float x,float y,float z);
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Matrix44 ZERO;
	static const Matrix44 IDENTITY;
private:
	//variables
	float M[16];
protected:
	//
};

}

#endif
