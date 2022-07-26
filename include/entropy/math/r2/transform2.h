#ifndef __transform2_h__
#define __transform2_h__

//local dependencies
#include <entropy\cfg.h>
#include <entropy\math\r2\matrix22.h>
#include <entropy\math\angle.h>
#include <entropy\math\r2\point2.h>
#include <entropy\math\r2\vector2.h>
#include <entropy\math\r2\normal2.h>
#include <entropy\math\r2\ray2.h>
#include <entropy\math\r2\line2.h>

namespace entropy
{

class Transform2
{
public:
	//constructors
	Transform2() {}
	Transform2(const Matrix22 &m,const Vector2 &translate=Vector2::ZERO,bool transFirst=false);
	Transform2(const Matrix22 &m,const Matrix22 &mInv,const Vector2 &translate=Vector2::ZERO,bool transFirst=false);
	Transform2(const Transform2 &right);
	//destructor
	~Transform2() {}
	//operator overloads
	Transform2 &operator=(const Transform2 &m);
	Point2 operator()(const Point2 &p) const;
	Vector2 operator()(const Vector2 &v) const;
	Normal2 operator()(const Normal2 &n) const; //add correct scale math
	Ray2 operator()(const Ray2 &r) const;
	Line2 operator()(const Line2 &l) const;
	Matrix22 operator()(const Matrix22 &m) const;
	Transform2 operator()(const Transform2 &t) const;
	bool operator==(const Transform2 &t) const;
	bool operator!=(const Transform2 &t) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Transform2 &t);
	//methods
	bool swapsHandedness() const;
	void invert();
	Transform2 inverse() const;
	//static methods
	static const Transform2 rotate(const Angle &angle);
	static const Transform2 translate(const Vector2 &translate);
	static const Transform2 scale(float x,float y);
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Transform2 ZERO;
	static const Transform2 IDENTITY;
private:
	//variables
	Matrix22 matrix;
	Matrix22 matrixInverse;
	//as it's not mathematically correct to translate
	//a point using a 2x2 matrix, we add a translation
	//vector as it's convenient to be able to also translate
	//the inverse translation is the negative of itself
	Vector2 trans;
	//should we translate first? needed as we can't
	//represent an affine transform with a 2x2 matrix
	bool transFirst;
protected:
	//
};

}

#endif
