//local dependencies
#include <entropy\math\r2\matrix22.h>
#include <entropy\math\math.h>

namespace entropy
{

//static variable definitions
const Matrix22 Matrix22::ZERO
(
	0.0f,0.0f,
	0.0f,0.0f
);
const Matrix22 Matrix22::IDENTITY
(
	1.0f,0.0f,
	0.0f,1.0f
);

Matrix22::Matrix22()
{
	M[0] = M[3] = 1.0f;
	M[1] = M[2] = 0.0f;
}

Matrix22::Matrix22(float m00,float m01,float m10,float m11)
{
	M[0] = m00;
	M[1] = m01;
	M[2] = m10;
	M[3] = m11;
}

Matrix22::Matrix22(const Vector2 &basis1,const Vector2 &basis2)
{
	//set first basis
	M[0] = basis1.x;
	M[2] = basis1.y;
	//set second basis
	M[1] = basis2.x;
	M[3] = basis2.y;
}

Matrix22::Matrix22(const Matrix22 &right)
{
	M[0] = right.M[0];
	M[1] = right.M[1];
	M[2] = right.M[2];
	M[3] = right.M[3];
}

Matrix22 &Matrix22::operator=(const Matrix22 &m)
{
	M[0] = m.M[0];
	M[1] = m.M[1];
	M[2] = m.M[2];
	M[3] = m.M[3];
	return *this;
}

Matrix22::operator float*()
{
	return &M[0];
}

//indexes begin at 0
float Matrix22::operator()(int r,int c) const
{
	ASSERT(r >= 0 && c >= 0 && r <= 1 && c <= 1);
	return M[(2*r) + c];
}

//indexes begin at 0
float &Matrix22::operator()(int r,int c)
{
	ASSERT(r >= 0 && c >= 0 && r <= 1 && c <= 1);
	return M[(2*r) + c];
}

Matrix22 Matrix22::operator+(const Matrix22 &m) const
{
	return Matrix22
	(
		M[0] + m.M[0],
		M[1] + m.M[1],
		M[2] + m.M[2],
		M[3] + m.M[3]
	);
}

Matrix22 &Matrix22::operator+=(const Matrix22 &m)
{
	M[0] += m.M[0];
	M[1] += m.M[1];
	M[2] += m.M[2];
	M[3] += m.M[3];
	return *this;
}

Matrix22 Matrix22::operator-() const
{
	return Matrix22
	(
		-M[0],-M[1],
		-M[2],-M[3]
	);
}

Matrix22 Matrix22::operator-(const Matrix22 &m) const
{
	return Matrix22
	(
		M[0] - m.M[0],
		M[1] - m.M[1],
		M[2] - m.M[2],
		M[3] - m.M[3]
	);
}

Matrix22 &Matrix22::operator-=(const Matrix22 &m)
{
	M[0] -= m.M[0];
	M[1] -= m.M[1];
	M[2] -= m.M[2];
	M[3] -= m.M[3];
	return *this;
}

Matrix22 Matrix22::operator*(float scalar) const
{
	return Matrix22
	(
		M[0] * scalar,
		M[1] * scalar,
		M[2] * scalar,
		M[3] * scalar
	);
}

Point2 Matrix22::operator*(const Point2 &p) const
{
	return Point2
	(
		M[0]*p.x + M[1]*p.y,
		M[2]*p.x + M[3]*p.y
	);
}

Vector2 Matrix22::operator*(const Vector2 &v) const
{
	return Vector2
	(
		M[0]*v.x + M[1]*v.y,
		M[2]*v.x + M[3]*v.y
	);
}

Normal2 Matrix22::operator*(const Normal2 &n) const
{
	//compute the transposed inverse to
	//use as normal transform matrix
	Matrix22 trInv = inverse().transpose();
	return Normal2
	(
		trInv.M[0]*n.x + trInv.M[1]*n.y,
		trInv.M[2]*n.x + trInv.M[3]*n.y
	);
}

Ray2 Matrix22::operator*(const Ray2 &r) const
{
	return Ray2
	(
		(*this) * r.o,
		(*this) * r.d
	);
}

Line2 Matrix22::operator*(const Line2 &l) const
{
	return Line2
	(
		(*this) * l.p,
		(*this) * l.d
	);
}

Matrix22 Matrix22::operator*(const Matrix22 &m) const
{
	return Matrix22
	(
		M[0]*m.M[0] + M[1]*m.M[2],
		M[0]*m.M[1] + M[1]*m.M[3],
		M[2]*m.M[0] + M[3]*m.M[2],
		M[2]*m.M[1] + M[3]*m.M[3]
	);
}

Matrix22 &Matrix22::operator*=(float scalar)
{
	M[0] *= scalar;
	M[1] *= scalar;
	M[2] *= scalar;
	M[3] *= scalar;
	return *this;
}

Matrix22 &Matrix22::operator*=(const Matrix22 &m)
{
	Matrix22 res
	(
		M[0]*m.M[0] + M[1]*m.M[2],
		M[0]*m.M[1] + M[1]*m.M[3],
		M[2]*m.M[0] + M[3]*m.M[2],
		M[2]*m.M[1] + M[3]*m.M[3]
	);
	*this = res;
	return *this;
}

Matrix22 Matrix22::operator/(float scalar) const
{
	float i = Math::inverse(scalar);
	return Matrix22
	(
		M[0] * i,
		M[1] * i,
		M[2] * i,
		M[3] * i
	);
}

Matrix22 &Matrix22::operator/=(float scalar)
{
	float i = Math::inverse(scalar);
	M[0] *= i;
	M[1] *= i;
	M[2] *= i;
	M[3] *= i;
	return *this;
}

bool Matrix22::operator==(const Matrix22 &m) const
{
	return	M[0] == m.M[0] &&
			M[1] == m.M[1] &&
			M[2] == m.M[2] &&
			M[3] == m.M[3];
}

bool Matrix22::operator!=(const Matrix22 &m) const
{
	return	M[0] != m.M[0] ||
			M[1] != m.M[1] ||
			M[2] != m.M[2] ||
			M[3] != m.M[3];
}

std::ostream &operator<<(std::ostream &out,const Matrix22 &m)
{
	out << '|' << m.M[0] << ',' << m.M[1] << "|\n";
	out << '|' << m.M[2] << ',' << m.M[3] << "|";
	return out;
}

void Matrix22::clean()
{
	for(int i=0; i<4; i++)
	{
		if(Math::isZero(M[i]))
		{
			M[i] = 0.0f;
		}
	}
}

float Matrix22::determinant() const
{
	return M[0]*M[3] - M[1]*M[2];
}

Matrix22 Matrix22::transpose() const
{
	return Matrix22
	(
		M[0],M[2],
		M[1],M[3]
	);
}

Matrix22 Matrix22::adjoint() const
{
	return Matrix22
	(
		M[3],-M[1],
		-M[2],M[0]
	);
}

Matrix22 Matrix22::inverse() const
{
	float det = determinant();
	//if determinant is zero then reutrn zero matrix
	if(Math::isZero(det))
	{
		return Matrix22::ZERO;
	}
	//compute the inverse by adjoint * reciprocal of determinant
	float invDet = Math::inverse(det);
	return adjoint() * invDet;
}

const Matrix22 Matrix22::rotate(const Angle &angle)
{
	float a = angle.asRadians();

	return Matrix22
	(
		Math::cos(a),-Math::sin(a),
		Math::sin(a),Math::cos(a)
	);
}

const Matrix22 Matrix22::scale(float x,float y)
{
	return Matrix22
	(
		x,0.0f,
		0.0f,y
	);
}

#ifdef DEBUG
void Matrix22::test()
{
	std::cout << "Matrix22 tests" << std::endl;
	std::cout << "Stream test (identity matrix): " << std::endl << Matrix22::IDENTITY << std::endl;
	std::cout << "Scale matrix of 3: " << std::endl << Matrix22::IDENTITY * 3.0f << std::endl;
	std::cout << "Inverse of scale matrix (3): " << std::endl << (Matrix22::IDENTITY * 3.0f).inverse() << std::endl;
	Matrix22 a(1,2,3,4),b(5,6,7,8);
	std::cout << "Matrix A: " << std::endl << a << std::endl;
	std::cout << "Matrix B: " << std::endl << b << std::endl;
	std::cout << "Index test on matrix A:\n";
	std::cout << "\tIndex 0: " << a[0] << std::endl;
	std::cout << "\tIndex 1: " << a[1] << std::endl;
	std::cout << "\tIndex 2: " << a[2] << std::endl;
	std::cout << "\tIndex 3: " << a[3] << std::endl;
	std::cout << "Inverse of matrix A: " << std::endl << a.inverse() << std::endl;
	std::cout << "Matrix A * its inverse should give identity: " << std::endl << a * a.inverse() << std::endl;

	//test rotation matrix
	float angle = 45.0f * Math::DEG_TO_RAD;
	Matrix22 rotation
	(
		Math::cos(angle),-Math::sin(angle),
		Math::sin(angle),Math::cos(angle)
	);
	Vector2 v = Vector2::X_AXIS;

	std::cout << "Vector to transform: " << v << std::endl;
	std::cout << "Rotation matrix (45 degrees): " << std::endl << rotation << std::endl;
	std::cout << "Transformation of vector by matrix: " << rotation * v << std::endl;

	std::cout << std::endl << Matrix22(1,2,3,4) * Vector2(5,6) << std::endl;

	std::cout << "testing (r,c) access (zero indexed): " << std::endl;
	std::cout << a << std::endl;
	std::cout << "a(0,0): " << a(0,0) << std::endl;
	std::cout << "a(0,1): " << a(0,1) << std::endl;
	std::cout << "a(1,0): " << a(1,0) << std::endl;
	std::cout << "a(1,1): " << a(1,1) << std::endl;

	std::cout << "Testing static rotate(angle) with angle of 45 degrees on vector (1,0): " << std::endl;
	std::cout << Matrix22::rotate(45.0f * Math::DEG_TO_RAD) * Vector2::X_AXIS << std::endl;

	//test angle
	std::cout << "Rotation matrix with Angle class holding 45.0f as Angle::DEGREES: " << std::endl;
	std::cout << Matrix22::rotate(Angle(45.0f,Angle::DEGREES)) << std::endl;
	std::cout << "Rotation matrix with Angle class holding Math::PI / 4 as Angle::RADIANS: " << std::endl;
	std::cout << Matrix22::rotate(Angle(Math::PI / 4.0f)) << std::endl;

	std::cout << Matrix22::rotate(Angle(45.0f,Angle::DEGREES)) * Vector2(0.5f,0.5f) << std::endl;

	std::cout << std::endl;
}
#endif

}
