//local dependencies
#include <entropy\math\r3\matrix33.h>
#include <entropy\math\math.h>

namespace entropy
{

//static variable definitions
const Matrix33 Matrix33::ZERO
(
	0.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f
);
const Matrix33 Matrix33::IDENTITY
(
	1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f
);

Matrix33::Matrix33()
{
	M[0] = M[4] = M[8] = 1.0f;
	M[1] = M[2] = M[3] = M[5] = M[6] = M[7] = 0.0f;
}

Matrix33::Matrix33
(
	float m00,float m01,float m02,
	float m10,float m11,float m12,
	float m20,float m21,float m22
)
{
	M[0] = m00;
	M[1] = m01;
	M[2] = m02;
	M[3] = m10;
	M[4] = m11;
	M[5] = m12;
	M[6] = m20;
	M[7] = m21;
	M[8] = m22;
}

Matrix33::Matrix33(const Vector3 &basis1,const Vector3 &basis2,const Vector3 &basis3)
{
	//set first basis
	M[0] = basis1.x;
	M[3] = basis1.y;
	M[6] = basis1.z;
	//set second basis
	M[1] = basis2.x;
	M[4] = basis2.y;
	M[7] = basis2.z;
	//set third basis
	M[2] = basis3.x;
	M[5] = basis3.y;
	M[8] = basis3.z;
}

Matrix33::Matrix33(const Matrix33 &right)
{
	M[0] = right.M[0];
	M[1] = right.M[1];
	M[2] = right.M[2];
	M[3] = right.M[3];
	M[4] = right.M[4];
	M[5] = right.M[5];
	M[6] = right.M[6];
	M[7] = right.M[7];
	M[8] = right.M[8];
}

Matrix33 &Matrix33::operator=(const Matrix33 &m)
{
	M[0] = m.M[0];
	M[1] = m.M[1];
	M[2] = m.M[2];
	M[3] = m.M[3];
	M[4] = m.M[4];
	M[5] = m.M[5];
	M[6] = m.M[6];
	M[7] = m.M[7];
	M[8] = m.M[8];
	return *this;
}

Matrix33::operator float*()
{
	return &M[0];
}

//indexes begin at 0
float Matrix33::operator()(int r,int c) const
{
	ASSERT(r >= 0 && c >= 0 && r <= 2 && c <= 2);
	return M[(3*r) + c];
}

//indexes begin at 0
float &Matrix33::operator()(int r,int c)
{
	ASSERT(r >= 0 && c >= 0 && r <= 2 && c <= 2);
	return M[(3*r) + c];
}

Matrix33 Matrix33::operator+(const Matrix33 &m) const
{
	return Matrix33
	(
		M[0] + m.M[0],
		M[1] + m.M[1],
		M[2] + m.M[2],
		M[3] + m.M[3],
		M[4] + m.M[4],
		M[5] + m.M[5],
		M[6] + m.M[6],
		M[7] + m.M[7],
		M[8] + m.M[8]
	);
}

Matrix33 &Matrix33::operator+=(const Matrix33 &m)
{
	M[0] += m.M[0];
	M[1] += m.M[1];
	M[2] += m.M[2];
	M[3] += m.M[3];
	M[4] += m.M[4];
	M[5] += m.M[5];
	M[6] += m.M[6];
	M[7] += m.M[7];
	M[8] += m.M[8];
	return *this;
}

Matrix33 Matrix33::operator-() const
{
	return Matrix33
	(
		-M[0],-M[1],-M[2],
		-M[3],-M[4],-M[5],
		-M[6],-M[7],-M[8]
	);
}

Matrix33 Matrix33::operator-(const Matrix33 &m) const
{
	return Matrix33
	(
		M[0] - m.M[0],
		M[1] - m.M[1],
		M[2] - m.M[2],
		M[3] - m.M[3],
		M[4] - m.M[4],
		M[5] - m.M[5],
		M[6] - m.M[6],
		M[7] - m.M[7],
		M[8] - m.M[8]
	);
}

Matrix33 &Matrix33::operator-=(const Matrix33 &m)
{
	M[0] -= m.M[0];
	M[1] -= m.M[1];
	M[2] -= m.M[2];
	M[3] -= m.M[3];
	M[4] -= m.M[4];
	M[5] -= m.M[5];
	M[6] -= m.M[6];
	M[7] -= m.M[7];
	M[8] -= m.M[8];
	return *this;
}

Matrix33 Matrix33::operator*(float scalar) const
{
	return Matrix33
	(
		M[0] * scalar,
		M[1] * scalar,
		M[2] * scalar,
		M[3] * scalar,
		M[4] * scalar,
		M[5] * scalar,
		M[6] * scalar,
		M[7] * scalar,
		M[8] * scalar
	);
}

Point3 Matrix33::operator*(const Point3 &p) const
{
	return Point3
	(
		M[0]*p.x + M[1]*p.y + M[2]*p.z,
		M[3]*p.x + M[4]*p.y + M[5]*p.z,
		M[6]*p.x + M[7]*p.y + M[8]*p.z
	);
}

Vector3 Matrix33::operator*(const Vector3 &v) const
{
	return Vector3
	(
		M[0]*v.x + M[1]*v.y + M[2]*v.z,
		M[3]*v.x + M[4]*v.y + M[5]*v.z,
		M[6]*v.x + M[7]*v.y + M[8]*v.z
	);
}

Normal3 Matrix33::operator*(const Normal3 &n) const
{
	//compute the transposed inverse to
	//use as normal transform matrix
	Matrix33 trInv = inverse().transpose();
	return Normal3
	(
		trInv.M[0]*n.x + trInv.M[1]*n.y + trInv.M[2]*n.z,
		trInv.M[3]*n.x + trInv.M[4]*n.y + trInv.M[5]*n.z,
		trInv.M[6]*n.x + trInv.M[7]*n.y + trInv.M[8]*n.z
	);
}

Ray3 Matrix33::operator*(const Ray3 &r) const
{
	return Ray3
	(
		(*this) * r.o,
		(*this) * r.d
	);
}

Line3 Matrix33::operator*(const Line3 &l) const
{
	return Line3
	(
		(*this) * l.p,
		(*this) * l.d
	);
}

BBox3 Matrix33::operator*(const BBox3 &b) const
{
	//TODO
	return BBox3();
}

Matrix33 Matrix33::operator*(const Matrix33 &m) const
{
	return Matrix33
	(
		M[0]*m.M[0] + M[1]*m.M[3] + M[2]*m.M[6], M[0]*m.M[1] + M[1]*m.M[4] + M[2]*m.M[7], M[0]*m.M[2] + M[1]*m.M[5] + M[2]*m.M[8],
		M[3]*m.M[0] + M[4]*m.M[3] + M[5]*m.M[6], M[3]*m.M[1] + M[4]*m.M[4] + M[5]*m.M[7], M[3]*m.M[2] + M[4]*m.M[5] + M[5]*m.M[8],
		M[6]*m.M[0] + M[7]*m.M[3] + M[8]*m.M[6], M[6]*m.M[1] + M[7]*m.M[4] + M[8]*m.M[7], M[6]*m.M[2] + M[7]*m.M[5] + M[8]*m.M[8]
	);
}

Matrix33 &Matrix33::operator*=(float scalar)
{
	M[0] *= scalar;
	M[1] *= scalar;
	M[2] *= scalar;
	M[3] *= scalar;
	M[4] *= scalar;
	M[5] *= scalar;
	M[6] *= scalar;
	M[7] *= scalar;
	M[8] *= scalar;
	return *this;
}

Matrix33 &Matrix33::operator*=(const Matrix33 &m)
{
	Matrix33 res
	(
		M[0]*m.M[0] + M[1]*m.M[3] + M[2]*m.M[6], M[0]*m.M[1] + M[1]*m.M[4] + M[2]*m.M[7], M[0]*m.M[2] + M[1]*m.M[5] + M[2]*m.M[8],
		M[3]*m.M[0] + M[4]*m.M[3] + M[5]*m.M[6], M[3]*m.M[1] + M[4]*m.M[4] + M[5]*m.M[7], M[3]*m.M[2] + M[4]*m.M[5] + M[5]*m.M[8],
		M[6]*m.M[0] + M[7]*m.M[3] + M[8]*m.M[6], M[6]*m.M[1] + M[7]*m.M[4] + M[8]*m.M[7], M[6]*m.M[2] + M[7]*m.M[5] + M[8]*m.M[8]
	);
	*this = res;
	return *this;
}

Matrix33 Matrix33::operator/(float scalar) const
{
	float i = Math::inverse(scalar);
	return Matrix33
	(
		M[0] * i,
		M[1] * i,
		M[2] * i,
		M[3] * i,
		M[4] * i,
		M[5] * i,
		M[6] * i,
		M[7] * i,
		M[8] * i
	);
}

Matrix33 &Matrix33::operator/=(float scalar)
{
	float i = Math::inverse(scalar);
	M[0] *= i;
	M[1] *= i;
	M[2] *= i;
	M[3] *= i;
	M[4] *= i;
	M[5] *= i;
	M[6] *= i;
	M[7] *= i;
	M[8] *= i;
	return *this;
}

bool Matrix33::operator==(const Matrix33 &m) const
{
	return	M[0] == m.M[0] &&
			M[1] == m.M[1] &&
			M[2] == m.M[2] &&
			M[3] == m.M[3] &&
			M[4] == m.M[4] &&
			M[5] == m.M[5] &&
			M[6] == m.M[6] &&
			M[7] == m.M[7] &&
			M[8] == m.M[8];
}

bool Matrix33::operator!=(const Matrix33 &m) const
{
	return	M[0] != m.M[0] ||
			M[1] != m.M[1] ||
			M[2] != m.M[2] ||
			M[3] != m.M[3] ||
			M[4] != m.M[4] ||
			M[5] != m.M[5] ||
			M[6] != m.M[6] ||
			M[7] != m.M[7] ||
			M[8] != m.M[8];
}

std::ostream &operator<<(std::ostream &out,const Matrix33 &m)
{
	out << '|' << m.M[0] << ',' << m.M[1] << ',' << m.M[2] << "|\n";
	out << '|' << m.M[3] << ',' << m.M[4] << ',' << m.M[5] << "|\n";
	out << '|' << m.M[6] << ',' << m.M[7] << ',' << m.M[8] << "|\n";
	return out;
}

void Matrix33::clean()
{
	for(int i=0; i<9; i++)
	{
		if(Math::isZero(M[i]))
		{
			M[i] = 0.0f;
		}
	}
}

float Matrix33::determinant() const
{
	return M[0]*(M[4]*M[8] - M[5]*M[7]) + M[1]*(M[5]*M[6] - M[3]*M[8]) + M[2]*(M[3]*M[7] - M[4]*M[6]);
}

Matrix33 Matrix33::transpose() const
{
	return Matrix33
	(
		M[0],M[3],M[6],
		M[1],M[4],M[7],
		M[2],M[5],M[8]
	);
}

Matrix33 Matrix33::adjoint() const
{
	return Matrix33
	(
		M[4]*M[8] - M[5]*M[7], M[2]*M[7] - M[1]*M[8], M[1]*M[5] - M[2]*M[4],
		M[5]*M[6] - M[3]*M[8], M[0]*M[8] - M[2]*M[6], M[2]*M[3] - M[0]*M[5],
		M[3]*M[7] - M[4]*M[6], M[1]*M[6] - M[0]*M[7], M[0]*M[4] - M[1]*M[3]
	);
}

Matrix33 Matrix33::inverse() const
{
	float det = determinant();
	//if determinant is zero then reutrn zero matrix
	if(Math::isZero(det))
	{
		return Matrix33::ZERO;
	}
	//compute the inverse by adjoint * reciprocal of determinant
	float invDet = Math::inverse(det);
	return adjoint() * invDet;
}

const Matrix33 Matrix33::rotate(const Angle &xAngle,const Angle &yAngle,const Angle &zAngle)
{
	float x = xAngle.asRadians();
	float y = yAngle.asRadians();
	float z = zAngle.asRadians();

	float Sx,Cx;
	Math::sinCos(x,Sx,Cx);
	float Sy,Cy;
	Math::sinCos(y,Sy,Cy);
	float Sz,Cz;
	Math::sinCos(z,Sz,Cz);

	return Matrix33
	(
		Cy*Cz, -Cy*Sz, Sy,
		Sx*Sy*Cz + Cx*Sz, -Sx*Sy*Sz + Cx*Cz, -Sx*Cy,
		-Cx*Sy*Cz + Sx*Sz, Cx*Sy*Sz + Sx*Cz, Cx*Cy
	);
}

const Matrix33 Matrix33::rotateX(const Angle &angle)
{
	float a = angle.asRadians();
	return Matrix33
	(
		1.0f,0.0f,0.0f,
		0.0f,Math::cos(a),-Math::sin(a),
		0.0f,Math::sin(a),Math::cos(a)
	);
}

const Matrix33 Matrix33::rotateY(const Angle &angle)
{
	float a = angle.asRadians();
	return Matrix33
	(
		Math::cos(a),0.0f,Math::sin(a),
		0.0f,1.0f,0.0f,
		-Math::sin(a),0.0f,Math::cos(a)
	);
}

const Matrix33 Matrix33::rotateZ(const Angle &angle)
{
	float a = angle.asRadians();
	return Matrix33
	(
		Math::cos(a),-Math::sin(a),0.0f,
		Math::sin(a),Math::cos(a),0.0f,
		0.0f,0.0f,1.0f
	);
}

const Matrix33 Matrix33::scale(float x,float y,float z)
{
	return Matrix33
	(
		x,0.0f,0.0f,
		0.0f,y,0.0f,
		0.0f,0.0f,z
	);
}

#ifdef DEBUG
void Matrix33::test()
{
	std::cout << "Matrix33 tests" << std::endl;
	std::cout << "Stream test (identity matrix): " << std::endl << Matrix33::IDENTITY << std::endl;
	std::cout << "Scale matrix of 3: " << std::endl << Matrix33::IDENTITY * 3.0f << std::endl;
	std::cout << "Inverse of scale matrix (3): " << std::endl << (Matrix33::IDENTITY * 3.0f).inverse() << std::endl;
	Matrix33 a(1,2,3,4,5,6,7,8,9),b(10,11,12,13,14,15,16,17,18);
	std::cout << "Matrix A: " << std::endl << a << std::endl;
	std::cout << "Matrix B: " << std::endl << b << std::endl;
	std::cout << "Index test on matrix A:\n";
	std::cout << "\tIndex 0: " << a[0] << std::endl;
	std::cout << "\tIndex 1: " << a[1] << std::endl;
	std::cout << "\tIndex 2: " << a[2] << std::endl;
	std::cout << "\tIndex 3: " << a[3] << std::endl;
	std::cout << "\tIndex 4: " << a[4] << std::endl;
	std::cout << "\tIndex 5: " << a[5] << std::endl;
	std::cout << "\tIndex 6: " << a[6] << std::endl;
	std::cout << "\tIndex 7: " << a[7] << std::endl;
	std::cout << "\tIndex 8: " << a[8] << std::endl;
	std::cout << "Inverse of matrix A: " << std::endl << a.inverse() << std::endl;
	std::cout << "Matrix A * its inverse should give identity: " << std::endl << a * a.inverse() << std::endl;

	//test rotation matrix
	float angle = 45.0f * Math::DEG_TO_RAD;
	Matrix33 rotation;/*
	(
		Math::cos(angle),-Math::sin(angle),
		Math::sin(angle),Math::cos(angle)
	);*/
	Vector3 v = Vector3::X_AXIS;

	std::cout << "Vector to transform: " << v << std::endl;
	std::cout << "Rotation matrix (45 degrees): " << std::endl << rotation << std::endl;
	std::cout << "Transformation of vector by matrix: " << rotation * v << std::endl;

	std::cout << std::endl << Matrix33(1,2,3,4,5,6,7,8,9) * Vector3(10,11,12) << std::endl;

	std::cout << "testing (r,c) access (zero indexed): " << std::endl;
	std::cout << a << std::endl;
	std::cout << "a(0,0): " << a(0,0) << std::endl;
	std::cout << "a(0,1): " << a(0,1) << std::endl;
	std::cout << "a(0,2): " << a(0,2) << std::endl;
	std::cout << "a(1,0): " << a(1,0) << std::endl;
	std::cout << "a(1,1): " << a(1,1) << std::endl;
	std::cout << "a(1,2): " << a(1,2) << std::endl;
	std::cout << "a(2,0): " << a(2,0) << std::endl;
	std::cout << "a(2,1): " << a(2,1) << std::endl;
	std::cout << "a(2,2): " << a(2,2) << std::endl;

	std::cout << "Testing static rotate(angle) with angle of 45 degrees on vector (1,0): " << std::endl;
	std::cout << Matrix33::rotate(45.0f * Math::DEG_TO_RAD,45.0f * Math::DEG_TO_RAD,45.0f * Math::DEG_TO_RAD) * Vector3::X_AXIS << std::endl;

	//test angle
	std::cout << "Rotation matrix with Angle class holding 45.0f as Angle::DEGREES: " << std::endl;
	std::cout << Matrix33::rotate(Angle(45.0f,Angle::DEGREES),Angle(45.0f,Angle::DEGREES),Angle(45.0f,Angle::DEGREES)) << std::endl;
	std::cout << "Rotation matrix with Angle class holding Math::PI / 4 as Angle::RADIANS: " << std::endl;
	std::cout << Matrix33::rotate(Angle(Math::PI / 4.0f),Angle(Math::PI / 4.0f),Angle(Math::PI / 4.0f)) << std::endl;

	std::cout << Matrix33::rotate(Angle(45.0f,Angle::DEGREES),Angle(45.0f,Angle::DEGREES),Angle(45.0f,Angle::DEGREES)) * Vector3(0.5f,0.5f,0.5f) << std::endl;

	std::cout << std::endl;

	Matrix33 Rx = Matrix33::rotateX(Angle(10,Angle::DEGREES));
	Matrix33 Ry = Matrix33::rotateY(Angle(20,Angle::DEGREES));
	Matrix33 Rz = Matrix33::rotateZ(Angle(30,Angle::DEGREES));
	Matrix33 Rxyz = Matrix33::rotate
	(
		Angle(10,Angle::DEGREES),
		Angle(20,Angle::DEGREES),
		Angle(30,Angle::DEGREES)
	);
	std::cout << "Units = degrees\n";
	std::cout << "Rx(10):\n" << Rx << std::endl;
	std::cout << "Ry(20):\n" << Ry << std::endl;
	std::cout << "Rz(30):\n" << Rz << std::endl;

	std::cout << "Rx(10)Ry(20)Rz(30):\n" << Rx*Ry*Rz << std::endl;
	std::cout << "Rxyz(10,20,30):\n" << Rxyz << std::endl;

	Matrix33 p = (Rxyz * Rxyz.inverse());
	p.clean();
	std::cout << p << std::endl;

	//test determinant

	std::cout << std::endl;
}
#endif

}
