#ifndef __transform3_h__
#define __transform3_h__

//local dependencies
#include <entropy\cfg.h>
#include <entropy\math\r3\matrix44.h>
#include <entropy\math\angle.h>
#include <entropy\math\r3\point3.h>
#include <entropy\math\r3\vector3.h>
#include <entropy\math\r3\normal3.h>
#include <entropy\math\r3\ray3.h>
#include <entropy\math\r3\line3.h>
#include <entropy\collision\r3\bbox3.h>

namespace entropy
{

class Transform3
{
public:
	//constructors
	Transform3() {}
	Transform3(const Matrix44 &m);
	Transform3(const Matrix44 &m,const Matrix44 &mInv);
	Transform3(const Transform3 &right);
	//destructor
	~Transform3() {}
	//operator overloads
	Transform3 &operator=(const Transform3 &m);
	operator float*();
	Point3 operator()(const Point3 &p) const;
	Vector3 operator()(const Vector3 &v) const;
	Normal3 operator()(const Normal3 &n) const;
	Ray3 operator()(const Ray3 &r) const;
	Line3 operator()(const Line3 &l) const;
	BBox3 operator()(const BBox3 &b) const;
	Matrix44 operator()(const Matrix44 &m) const;
	Transform3 operator()(const Transform3 &t) const;
	bool operator==(const Transform3 &t) const;
	bool operator!=(const Transform3 &t) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Transform3 &t);
	//methods
	bool swapsHandedness() const;
	void invert();
	Transform3 inverse() const;
	Transform3 transpose() const { return Transform3(matrix.transpose(),matrixInverse.transpose()); }
	//static methods
	static const Transform3 rotate(const Angle &xAngle,const Angle &yAngle,const Angle &zAngle);
	static const Transform3 rotateX(const Angle &angle);
	static const Transform3 rotateY(const Angle &angle);
	static const Transform3 rotateZ(const Angle &angle);
	static const Transform3 translate(float x,float y,float z);
	static const Transform3 translate(const Vector3 &trans);
	static const Transform3 scale(float x,float y,float z);
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Transform3 ZERO;
	static const Transform3 IDENTITY;
private:
	//variables
	Matrix44 matrix;
	Matrix44 matrixInverse;
protected:
	//
};

}

#endif
