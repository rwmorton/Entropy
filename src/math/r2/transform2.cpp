//local dependencies
#include <entropy\math\r2\transform2.h>
#include <entropy\math\math.h>
#include <entropy\util\algo.h>

namespace entropy
{

//static variable definitions
const Transform2 Transform2::ZERO(Matrix22::ZERO,Matrix22::ZERO);
const Transform2 Transform2::IDENTITY; //defaults to identity transform

Transform2::Transform2(const Matrix22 &m,const Vector2 &translate,bool transFirst)
{
	matrix = m;
	matrixInverse = m.inverse();
	trans = translate;
	this->transFirst = transFirst;
}

Transform2::Transform2(const Matrix22 &m,const Matrix22 &mInv,const Vector2 &translate,bool transFirst)
{
	matrix = m;
	matrixInverse = mInv;
	trans = translate;
	this->transFirst = transFirst;
}

Transform2::Transform2(const Transform2 &right)
{
	matrix = right.matrix;
	matrixInverse = right.matrixInverse;
	trans = right.trans;
	transFirst = right.transFirst;
}

Transform2 &Transform2::operator=(const Transform2 &m)
{
	matrix = m.matrix;
	matrixInverse = m.matrixInverse;
	trans = m.trans;
	transFirst = m.transFirst;
	return *this;
}

Point2 Transform2::operator()(const Point2 &p) const
{
	//an "affine" transform can be applied to a point
	if(transFirst)
	{
		//apply our "affine" transform
		//then
		//apply our linear transform
		Point2 p_trans(trans.x+p.x,trans.y+p.y);
		return matrix * p_trans;
	}
	else
	{
		//apply our linear transform
		//then
		//apply our "affine" transform
		return (matrix * p) + trans;
	}
}

Vector2 Transform2::operator()(const Vector2 &v) const
{
	//only linear transforms apply here
	return matrix * v;
}

Normal2 Transform2::operator()(const Normal2 &n) const
{
	//only linear transforms apply here
	return matrix * n;
}

Ray2 Transform2::operator()(const Ray2 &r) const
{
	//an "affine" transform can be applied
	//to the rays origin (which is a point)
	return Ray2
	(
		(*this)(r.o),
		matrix * r.d	//induces a rotation only
	);

	//return matrix * r;
}

Line2 Transform2::operator()(const Line2 &l) const
{
	//an "affine" transform can be applied
	//to the lines origin (which is a point)
	return Line2
	(
		(*this)(l.p),
		matrix * l.d	//induces a rotation only
	);
}

Matrix22 Transform2::operator()(const Matrix22 &m) const
{
	return matrix * m;
}

Transform2 Transform2::operator()(const Transform2 &t) const
{
	//linear and "affine" transformation
	return Transform2
	(
		matrix * t.matrix,
		matrixInverse * t.matrixInverse,
		trans + t.trans
	);
}

bool Transform2::operator==(const Transform2 &t) const
{
	return matrix == t.matrix && matrixInverse == t.matrixInverse && trans == t.trans;
}

bool Transform2::operator!=(const Transform2 &t) const
{
	return matrix != t.matrix || matrixInverse != t.matrixInverse || trans != t.trans;
}

std::ostream &operator<<(std::ostream &out,const Transform2 &t)
{
	out << t.matrix << std::endl;
	out << t.matrixInverse << std::endl;
	out << t.trans;
	return out;
}

bool Transform2::swapsHandedness() const
{
	return matrix.determinant() < 0;
}

void Transform2::invert()
{
	Algo::swap<Matrix22>(matrix,matrixInverse);
}

Transform2 Transform2::inverse() const
{
	return Transform2(matrixInverse,matrix,-trans,!transFirst);
}

const Transform2 Transform2::rotate(const Angle &angle)
{
	Transform2 transform(Matrix22::rotate(angle));
	transform.matrixInverse = transform.matrix.transpose(); //inverse of a rotation matrix is its transpose
	return transform;
}

const Transform2 Transform2::translate(const Vector2 &translate)
{
	return Transform2
	(
		Matrix22::IDENTITY,
		Matrix22::IDENTITY,
		translate
	);
}

const Transform2 Transform2::scale(float x,float y)
{
	return Transform2
	(
		Matrix22::scale(x,y),
		Matrix22
		(
			Math::inverse(x),0.0f,
			0.0f,Math::inverse(y)
		)
	);
}

#ifdef DEBUG
void Transform2::test()
{
	std::cout << "Transform2 test" << std::endl;

	Point2 p(1,0);
	Transform2 t1 = Transform2::rotate(Angle(45.0f,Angle::DEGREES));
	Transform2 t2 = Transform2::rotate(Angle(45.0f,Angle::DEGREES));
	Transform2 t3 = Transform2::translate(Vector2(1,1));
	Transform2 t21 = t2(t1);
	Transform2 t321 = t3(t2(t1));

	std::cout << "Rotate (1,0) 45 degrees: " << t1(p) << std::endl;
	std::cout << "Rotate again 45 degrees: " << t2(t1(p)) << std::endl;
	std::cout << "Composite transform of the above: " << t21(p) << std::endl;
	std::cout << "Inverse of composite: " << (t21.inverse())(t21(p)) << std::endl;

	std::cout << "Rotate 45 degrees, rotate 45 degrees, translate by (1,1), should move point (1,0) to (1,2): " << t321(p) << std::endl;
	std::cout << "Inverse of above transform, should give (1,0): " << (t321.inverse())(t321(p)) << std::endl;

	std::cout << std::endl;

	std::cout << "Test ray transforms. Only 'affine' transforms should be applied to the origin (which is ";
	std::cout << "a point), and linear transforms to the direction (a vector)" << std::endl;
	Ray2 r(Point2(0,0),Vector2::X_AXIS);
	std::cout << "Ray r ( (0,0), (1,0) ): " << r << std::endl;
	//rotate 45 degrees
	std::cout << "Ray rotated 45 degrees, should give ( (0,0), (0.707,0.707) ): " << t1(r) << std::endl;
	//rotate 45 degrees and translate by (1,1)
	Transform2 RT = t1(Transform2::translate(Vector2(1,1)));
	std::cout << "Ray rotated 45 degrees and translated by (1,1), should give ( (1,1), (0.707,0.707) ): " << RT(r) << std::endl;
	std::cout << "Take ray back to its original location, should give ( (0,0), (1,0) ): " << (RT.inverse())(RT(r)) << std::endl;

	//std::cout << "t1\n" << t1 << std::endl;
	//std::cout << "t2\n" << t2 << std::endl;
	//std::cout << "t21\n" << t21 << std::endl;

	std::cout << std::endl;
}
#endif

}
