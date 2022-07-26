//local dependencies
#include <entropy\math\r3\transform3.h>
#include <entropy\math\math.h>
#include <entropy\util\algo.h>

namespace entropy
{

//static variable definitions
const Transform3 Transform3::ZERO(Matrix44::ZERO,Matrix44::ZERO);
const Transform3 Transform3::IDENTITY; //defaults to identity transform

Transform3::Transform3(const Matrix44 &m)
{
	matrix = m;
	matrixInverse = m.inverse();
}

Transform3::Transform3(const Matrix44 &m,const Matrix44 &mInv)
{
	matrix = m;
	matrixInverse = mInv;
}

Transform3::Transform3(const Transform3 &right)
{
	matrix = right.matrix;
	matrixInverse = right.matrixInverse;
}

Transform3 &Transform3::operator=(const Transform3 &m)
{
	matrix = m.matrix;
	matrixInverse = m.matrixInverse;
	return *this;
}

Transform3::operator float*()
{
	return matrix;
}

Point3 Transform3::operator()(const Point3 &p) const
{
	//affine transform
	return matrix * p;
}

Vector3 Transform3::operator()(const Vector3 &v) const
{
	//only linear transforms apply here
	return matrix * v;
}

Normal3 Transform3::operator()(const Normal3 &n) const
{
	//only linear transforms apply here
	return matrix * n;
}

Ray3 Transform3::operator()(const Ray3 &r) const
{
	return matrix * r;
}

Line3 Transform3::operator()(const Line3 &l) const
{
	return matrix * l;
}

BBox3 Transform3::operator()(const BBox3 &b) const
{
	//TODO
	return BBox3();
}

Matrix44 Transform3::operator()(const Matrix44 &m) const
{
	return matrix * m;
}

Transform3 Transform3::operator()(const Transform3 &t) const
{
	//linear and "affine" transformation
	return Transform3
	(
		matrix * t.matrix,
		matrixInverse * t.matrixInverse
	);
}

bool Transform3::operator==(const Transform3 &t) const
{
	return matrix == t.matrix && matrixInverse == t.matrixInverse;
}

bool Transform3::operator!=(const Transform3 &t) const
{
	return matrix != t.matrix || matrixInverse != t.matrixInverse;
}

std::ostream &operator<<(std::ostream &out,const Transform3 &t)
{
	out << t.matrix << std::endl;
	out << t.matrixInverse << std::endl;
	return out;
}

bool Transform3::swapsHandedness() const
{
	return matrix.determinant() < 0;
}

void Transform3::invert()
{
	Algo::swap<Matrix44>(matrix,matrixInverse);
}

Transform3 Transform3::inverse() const
{
	return Transform3(matrixInverse,matrix);
}

const Transform3 Transform3::rotate(const Angle &xAngle,const Angle &yAngle,const Angle &zAngle)
{
	Transform3 transform(Matrix44::rotate(xAngle,yAngle,zAngle));
	transform.matrixInverse = transform.matrix.transpose(); //inverse of a rotation matrix is its transpose
	return transform;
}

const Transform3 Transform3::rotateX(const Angle &angle)
{
	Transform3 transform(Matrix44::rotateX(angle));
	transform.matrixInverse = transform.matrix.transpose(); //inverse of a rotation matrix is its transpose
	return transform;
}

const Transform3 Transform3::rotateY(const Angle &angle)
{
	Transform3 transform(Matrix44::rotateY(angle));
	transform.matrixInverse = transform.matrix.transpose(); //inverse of a rotation matrix is its transpose
	return transform;
}

const Transform3 Transform3::rotateZ(const Angle &angle)
{
	Transform3 transform(Matrix44::rotateZ(angle));
	transform.matrixInverse = transform.matrix.transpose(); //inverse of a rotation matrix is its transpose
	return transform;
}

const Transform3 Transform3::translate(float x,float y,float z)
{
	return Transform3
	(
		Matrix44::translate(x,y,z),
		Matrix44
		(
			1.0f,0.0f,0.0f,-x,
			0.0f,1.0f,0.0f,-y,
			0.0f,0.0f,1.0f,-z,
			0.0f,0.0f,0.0f,1.0f
		)
	);
}

const Transform3 Transform3::translate(const Vector3 &trans)
{
	return Transform3
	(
		Matrix44::translate(trans.x,trans.y,trans.z),
		Matrix44
		(
			1.0f,0.0f,0.0f,-trans.x,
			0.0f,1.0f,0.0f,-trans.y,
			0.0f,0.0f,1.0f,-trans.z,
			0.0f,0.0f,0.0f,1.0f
		)
	);
}

const Transform3 Transform3::scale(float x,float y,float z)
{
	return Transform3
	(
		Matrix44::scale(x,y,z),
		Matrix44
		(
			Math::inverse(x),0.0f,0.0f,0.0f,
			0.0f,Math::inverse(y),0.0f,0.0f,
			0.0f,0.0f,Math::inverse(z),0.0f,
			0.0f,0.0f,0.0f,1.0f
		)
	);
}

#ifdef DEBUG
void Transform3::test()
{
	std::cout << "Transform3 test" << std::endl;

	// THIS IS COPIED FROM Transform2 test() - REPLACE WITH NEW TESTS
	/*
	Point3 p(1,0,0);
	Transform3 t1 = Transform3::rotate(Angle(45.0f,Angle::DEGREES),Angle(45.0f,Angle::DEGREES),Angle(45.0f,Angle::DEGREES));
	Transform3 t2 = Transform3::rotate(Angle(45.0f,Angle::DEGREES),Angle(45.0f,Angle::DEGREES),Angle(45.0f,Angle::DEGREES));
	Transform3 t3 = Transform3::translate(Vector3(1,1,1));
	Transform3 t21 = t2(t1);
	Transform3 t321 = t3(t2(t1));

	std::cout << "Rotate (1,0) 45 degrees: " << t1(p) << std::endl;
	std::cout << "Rotate again 45 degrees: " << t2(t1(p)) << std::endl;
	std::cout << "Composite transform of the above: " << t21(p) << std::endl;
	std::cout << "Inverse of composite: " << (t21.inverse())(t21(p)) << std::endl;

	std::cout << "Rotate 45 degrees, rotate 45 degrees, translate by (1,1), should move point (1,0) to (1,2): " << t321(p) << std::endl;
	std::cout << "Inverse of above transform, should give (1,0): " << (t321.inverse())(t321(p)) << std::endl;

	std::cout << std::endl;

	std::cout << "Test ray transforms. Only 'affine' transforms should be applied to the origin (which is ";
	std::cout << "a point), and linear transforms to the direction (a vector)" << std::endl;
	Ray3 r(Point3(0,0,0),Vector3::X_AXIS);
	std::cout << "Ray r ( (0,0), (1,0) ): " << r << std::endl;
	//rotate 45 degrees
	std::cout << "Ray rotated 45 degrees, should give ( (0,0,0), (0.707,0.707,0) ): " << t1(r) << std::endl;
	//rotate 45 degrees and translate by (1,1)
	Transform3 RT = t1(Transform3::translate(Vector3(1,1,1)));
	std::cout << "Ray rotated 45 degrees and translated by (1,1,1), should give ( (1,1,1), (0.707,0.707,0) ): " << RT(r) << std::endl;
	std::cout << "Take ray back to its original location, should give ( (0,0,0), (1,0,0) ): " << (RT.inverse())(RT(r)) << std::endl;
	*/

	std::cout << std::endl;
}
#endif

}
