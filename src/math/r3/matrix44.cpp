//local dependencies
#include <entropy\math\r3\matrix44.h>
#include <entropy\math\math.h>

namespace entropy
{

//static variable definitions
const Matrix44 Matrix44::ZERO
(
	0.0f,0.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f,0.0f
);
const Matrix44 Matrix44::IDENTITY
(
	1.0f,0.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,0.0f,1.0f
);

Matrix44::Matrix44()
{
	M[0] = M[5] = M[10] = M[15] = 1.0f;
	M[1] = M[2] = M[3] = M[4] = M[6] = M[7] = M[8] = M[9] = M[11] = M[12] = M[13] = M[14] = 0.0f;
}

Matrix44::Matrix44
(
	float m00,float m01,float m02,float m03,
	float m10,float m11,float m12,float m13,
	float m20,float m21,float m22,float m23,
	float m30,float m31,float m32,float m33
)
{
	M[0] = m00;
	M[1] = m01;
	M[2] = m02;
	M[3] = m03;
	M[4] = m10;
	M[5] = m11;
	M[6] = m12;
	M[7] = m13;
	M[8] = m20;
	M[9] = m21;
	M[10] = m22;
	M[11] = m23;
	M[12] = m30;
	M[13] = m31;
	M[14] = m32;
	M[15] = m33;
}

Matrix44::Matrix44(const Vector3 &basis1,const Vector3 &basis2,const Vector3 &basis3)
{
	//set first basis
	M[0] = basis1.x;
	M[4] = basis1.y;
	M[8] = basis1.z;
	//set second basis
	M[1] = basis2.x;
	M[5] = basis2.y;
	M[9] = basis2.z;
	//set third basis
	M[2] = basis3.x;
	M[6] = basis3.y;
	M[10] = basis3.z;
	//set rest
	M[15] = 1.0f;
	M[3] = M[7] = M[11] = M[12] = M[13] = M[14] = 0.0f;
}

Matrix44::Matrix44(const Matrix44 &right)
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
	M[9] = right.M[9];
	M[10] = right.M[10];
	M[11] = right.M[11];
	M[12] = right.M[12];
	M[13] = right.M[13];
	M[14] = right.M[14];
	M[15] = right.M[15];
}

Matrix44 &Matrix44::operator=(const Matrix44 &m)
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
	M[9] = m.M[9];
	M[10] = m.M[10];
	M[11] = m.M[11];
	M[12] = m.M[12];
	M[13] = m.M[13];
	M[14] = m.M[14];
	M[15] = m.M[15];
	return *this;
}

Matrix44::operator float*()
{
	return &M[0];
}

//indexes begin at 0
float Matrix44::operator()(int r,int c) const
{
	ASSERT(r >= 0 && c >= 0 && r <= 3 && c <= 3);
	return M[(3*r) + c];
}

//indexes begin at 0
float &Matrix44::operator()(int r,int c)
{
	ASSERT(r >= 0 && c >= 0 && r <= 3 && c <= 3);
	return M[(3*r) + c];
}

Matrix44 Matrix44::operator+(const Matrix44 &m) const
{
	return Matrix44
	(
		M[0] + m.M[0],
		M[1] + m.M[1],
		M[2] + m.M[2],
		M[3] + m.M[3],
		M[4] + m.M[4],
		M[5] + m.M[5],
		M[6] + m.M[6],
		M[7] + m.M[7],
		M[8] + m.M[8],
		M[9] + m.M[9],
		M[10] + m.M[10],
		M[11] + m.M[11],
		M[12] + m.M[12],
		M[13] + m.M[13],
		M[14] + m.M[14],
		M[15] + m.M[15]
	);
}

Matrix44 &Matrix44::operator+=(const Matrix44 &m)
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
	M[9] += m.M[9];
	M[10] += m.M[10];
	M[11] += m.M[11];
	M[12] += m.M[12];
	M[13] += m.M[13];
	M[14] += m.M[14];
	M[15] += m.M[15];
	return *this;
}

Matrix44 Matrix44::operator-() const
{
	return Matrix44
	(
		-M[0],-M[1],-M[2],-M[3],
		-M[4],-M[5],-M[6],-M[7],
		-M[8],-M[9],-M[10],-M[11],
		-M[12],-M[13],-M[14],-M[15]
	);
}

Matrix44 Matrix44::operator-(const Matrix44 &m) const
{
	return Matrix44
	(
		M[0] - m.M[0],
		M[1] - m.M[1],
		M[2] - m.M[2],
		M[3] - m.M[3],
		M[4] - m.M[4],
		M[5] - m.M[5],
		M[6] - m.M[6],
		M[7] - m.M[7],
		M[8] - m.M[8],
		M[9] - m.M[9],
		M[10] - m.M[10],
		M[11] - m.M[11],
		M[12] - m.M[12],
		M[13] - m.M[13],
		M[14] - m.M[14],
		M[15] - m.M[15]
	);
}

Matrix44 &Matrix44::operator-=(const Matrix44 &m)
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
	M[9] -= m.M[9];
	M[10] -= m.M[10];
	M[11] -= m.M[11];
	M[12] -= m.M[12];
	M[13] -= m.M[13];
	M[14] -= m.M[14];
	M[15] -= m.M[15];
	return *this;
}

Matrix44 Matrix44::operator*(float scalar) const
{
	return Matrix44
	(
		M[0] * scalar,
		M[1] * scalar,
		M[2] * scalar,
		M[3] * scalar,
		M[4] * scalar,
		M[5] * scalar,
		M[6] * scalar,
		M[7] * scalar,
		M[8] * scalar,
		M[9] * scalar,
		M[10] * scalar,
		M[11] * scalar,
		M[12] * scalar,
		M[13] * scalar,
		M[14] * scalar,
		M[15] * scalar
	);
}

Point3 Matrix44::operator*(const Point3 &p) const
{
	return Point3
	(
		M[0]*p.x + M[1]*p.y + M[2]*p.z + M[3],
		M[4]*p.x + M[5]*p.y + M[6]*p.z + M[7],
		M[8]*p.x + M[9]*p.y + M[10]*p.z + M[11]
	);
}

Vector3 Matrix44::operator*(const Vector3 &v) const
{
	return Vector3
	(
		M[0]*v.x + M[1]*v.y + M[2]*v.z,
		M[4]*v.x + M[5]*v.y + M[6]*v.z,
		M[8]*v.x + M[9]*v.y + M[10]*v.z
	);
}

Normal3 Matrix44::operator*(const Normal3 &n) const
{
	//compute the transposed inverse to
	//use as normal transform matrix
	Matrix44 trInv = inverse().transpose();
	return Normal3
	(
		trInv.M[0]*n.x + trInv.M[1]*n.y + trInv.M[2]*n.z,
		trInv.M[4]*n.x + trInv.M[5]*n.y + trInv.M[6]*n.z,
		trInv.M[8]*n.x + trInv.M[9]*n.y + trInv.M[10]*n.z
	);
}

Ray3 Matrix44::operator*(const Ray3 &r) const
{
	return Ray3
	(
		(*this) * r.o,
		(*this) * r.d
	);
}

Line3 Matrix44::operator*(const Line3 &l) const
{
	return Line3
	(
		(*this) * l.p,
		(*this) * l.d
	);
}

BBox3 Matrix44::operator*(const BBox3 &b) const
{
	//TODO
	return BBox3();
}

Matrix44 Matrix44::operator*(const Matrix44 &m) const
{
	return Matrix44
	(
		M[0]*m.M[0] + M[1]*m.M[4] + M[2]*m.M[8] + M[3]*m.M[12],
		M[0]*m.M[1] + M[1]*m.M[5] + M[2]*m.M[9] + M[3]*m.M[13],
		M[0]*m.M[2] + M[1]*m.M[6] + M[2]*m.M[10] + M[3]*m.M[14],
		M[0]*m.M[3] + M[1]*m.M[7] + M[2]*m.M[11] + M[3]*m.M[15],
		M[4]*m.M[0] + M[5]*m.M[4] + M[6]*m.M[8] + M[7]*m.M[12],
		M[4]*m.M[1] + M[5]*m.M[5] + M[6]*m.M[9] + M[7]*m.M[13],
		M[4]*m.M[2] + M[5]*m.M[6] + M[6]*m.M[10] + M[7]*m.M[14],
		M[4]*m.M[3] + M[5]*m.M[7] + M[6]*m.M[11] + M[7]*m.M[15],
		M[8]*m.M[0] + M[9]*m.M[4] + M[10]*m.M[8] + M[11]*m.M[12],
		M[8]*m.M[1] + M[9]*m.M[5] + M[10]*m.M[9] + M[11]*m.M[13],
		M[8]*m.M[2] + M[9]*m.M[6] + M[10]*m.M[10] + M[11]*m.M[14],
		M[8]*m.M[3] + M[9]*m.M[7] + M[10]*m.M[11] + M[11]*m.M[15],
		M[12]*m.M[0] + M[13]*m.M[4] + M[14]*m.M[8] + M[15]*m.M[12],
		M[12]*m.M[1] + M[13]*m.M[5] + M[14]*m.M[9] + M[15]*m.M[13],
		M[12]*m.M[2] + M[13]*m.M[6] + M[14]*m.M[10] + M[15]*m.M[14],
		M[12]*m.M[3] + M[13]*m.M[7] + M[14]*m.M[11] + M[15]*m.M[15]
	);
}

Matrix44 &Matrix44::operator*=(float scalar)
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
	M[9] *= scalar;
	M[10] *= scalar;
	M[11] *= scalar;
	M[12] *= scalar;
	M[13] *= scalar;
	M[14] *= scalar;
	M[15] *= scalar;
	return *this;
}

Matrix44 &Matrix44::operator*=(const Matrix44 &m)
{
	Matrix44 res
	(
		M[0]*m.M[0] + M[1]*m.M[4] + M[2]*m.M[8] + M[3]*m.M[12],
		M[0]*m.M[1] + M[1]*m.M[5] + M[2]*m.M[9] + M[3]*m.M[13],
		M[0]*m.M[2] + M[1]*m.M[6] + M[2]*m.M[10] + M[3]*m.M[14],
		M[0]*m.M[3] + M[1]*m.M[7] + M[2]*m.M[11] + M[3]*m.M[15],
		M[4]*m.M[0] + M[5]*m.M[4] + M[6]*m.M[8] + M[7]*m.M[12],
		M[4]*m.M[1] + M[5]*m.M[5] + M[6]*m.M[9] + M[7]*m.M[13],
		M[4]*m.M[2] + M[5]*m.M[6] + M[6]*m.M[10] + M[7]*m.M[14],
		M[4]*m.M[3] + M[5]*m.M[7] + M[6]*m.M[11] + M[7]*m.M[15],
		M[8]*m.M[0] + M[9]*m.M[4] + M[10]*m.M[8] + M[11]*m.M[12],
		M[8]*m.M[1] + M[9]*m.M[5] + M[10]*m.M[9] + M[11]*m.M[13],
		M[8]*m.M[2] + M[9]*m.M[6] + M[10]*m.M[10] + M[11]*m.M[14],
		M[8]*m.M[3] + M[9]*m.M[7] + M[10]*m.M[11] + M[11]*m.M[15],
		M[12]*m.M[0] + M[13]*m.M[4] + M[14]*m.M[8] + M[15]*m.M[12],
		M[12]*m.M[1] + M[13]*m.M[5] + M[14]*m.M[9] + M[15]*m.M[13],
		M[12]*m.M[2] + M[13]*m.M[6] + M[14]*m.M[10] + M[15]*m.M[14],
		M[12]*m.M[3] + M[13]*m.M[7] + M[14]*m.M[11] + M[15]*m.M[15]
	);
	*this = res;
	return *this;
}

Matrix44 Matrix44::operator/(float scalar) const
{
	float i = Math::inverse(scalar);
	return Matrix44
	(
		M[0] * i,
		M[1] * i,
		M[2] * i,
		M[3] * i,
		M[4] * i,
		M[5] * i,
		M[6] * i,
		M[7] * i,
		M[8] * i,
		M[9] * i,
		M[10] * i,
		M[11] * i,
		M[12] * i,
		M[13] * i,
		M[14] * i,
		M[15] * i
	);
}

Matrix44 &Matrix44::operator/=(float scalar)
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
	M[9] *= i;
	M[10] *= i;
	M[11] *= i;
	M[12] *= i;
	M[13] *= i;
	M[14] *= i;
	M[15] *= i;
	return *this;
}

bool Matrix44::operator==(const Matrix44 &m) const
{
	return	M[0] == m.M[0] &&
			M[1] == m.M[1] &&
			M[2] == m.M[2] &&
			M[3] == m.M[3] &&
			M[4] == m.M[4] &&
			M[5] == m.M[5] &&
			M[6] == m.M[6] &&
			M[7] == m.M[7] &&
			M[8] == m.M[8] &&
			M[9] == m.M[9] &&
			M[10] == m.M[10] &&
			M[11] == m.M[11] &&
			M[12] == m.M[12] &&
			M[13] == m.M[13] &&
			M[14] == m.M[14] &&
			M[15] == m.M[15];
}

bool Matrix44::operator!=(const Matrix44 &m) const
{
	return	M[0] != m.M[0] ||
			M[1] != m.M[1] ||
			M[2] != m.M[2] ||
			M[3] != m.M[3] ||
			M[4] != m.M[4] ||
			M[5] != m.M[5] ||
			M[6] != m.M[6] ||
			M[7] != m.M[7] ||
			M[8] != m.M[8] ||
			M[9] != m.M[9] ||
			M[10] != m.M[10] ||
			M[11] != m.M[11] ||
			M[12] != m.M[12] ||
			M[13] != m.M[13] ||
			M[14] != m.M[14] ||
			M[15] != m.M[15];
}

std::ostream &operator<<(std::ostream &out,const Matrix44 &m)
{
	out << '|' << m.M[0] << ',' << m.M[1] << ',' << m.M[2] << ',' << m.M[3] << "|\n";
	out << '|' << m.M[4] << ',' << m.M[5] << ',' << m.M[6] << ',' << m.M[7] << "|\n";
	out << '|' << m.M[8] << ',' << m.M[9] << ',' << m.M[10] << ',' << m.M[11] << "|\n";
	out << '|' << m.M[12] << ',' << m.M[13] << ',' << m.M[14] << ',' << m.M[15] << "|\n";
	return out;
}

void Matrix44::clean()
{
	for(int i=0; i<16; i++)
	{
		if(Math::isZero(M[i]))
		{
			M[i] = 0.0f;
		}
	}
}

float Matrix44::determinant() const
{
	float A0 = M[0]*M[5] - M[1]*M[4];
	float A1 = M[0]*M[6] - M[2]*M[4];
	float A2 = M[0]*M[7] - M[3]*M[4];
	float A3 = M[1]*M[6] - M[2]*M[5];
	float A4 = M[1]*M[7] - M[3]*M[5];
	float A5 = M[2]*M[7] - M[3]*M[6];
	float B0 = M[8]*M[13] - M[9]*M[12];
	float B1 = M[8]*M[14] - M[10]*M[12];
	float B2 = M[8]*M[15] - M[11]*M[12];
	float B3 = M[9]*M[14] - M[10]*M[13];
	float B4 = M[9]*M[15] - M[11]*M[13];
	float B5 = M[10]*M[15] - M[11]*M[14];
	return A0*B5 - A1*B4 + A2*B3 + A3*B2 - A4*B1 + A5*B0;
}

Matrix44 Matrix44::transpose() const
{
	return Matrix44
	(
		M[0],M[4],M[8],M[12],
		M[1],M[5],M[9],M[13],
		M[2],M[6],M[10],M[14],
		M[3],M[7],M[11],M[15]
	);
}

Matrix44 Matrix44::adjoint() const
{
	float A0 = M[0]*M[5] - M[1]*M[4];
	float A1 = M[0]*M[6] - M[2]*M[4];
	float A2 = M[0]*M[7] - M[3]*M[4];
	float A3 = M[1]*M[6] - M[2]*M[5];
	float A4 = M[1]*M[7] - M[3]*M[5];
	float A5 = M[2]*M[7] - M[3]*M[6];
	float B0 = M[8]*M[13] - M[9]*M[12];
	float B1 = M[8]*M[14] - M[10]*M[12];
	float B2 = M[8]*M[15] - M[11]*M[12];
	float B3 = M[9]*M[14] - M[10]*M[13];
	float B4 = M[9]*M[15] - M[11]*M[13];
	float B5 = M[10]*M[15] - M[11]*M[14];

    return Matrix44
	(
		+ M[5]*B5 - M[6]*B4 + M[7]*B3,
		- M[1]*B5 + M[2]*B4 - M[3]*B3,
		+ M[13]*A5 - M[14]*A4 + M[15]*A3,
		- M[9]*A5 + M[10]*A4 - M[11]*A3,
		- M[4]*B5 + M[6]*B2 - M[7]*B1,
		+ M[0]*B5 - M[2]*B2 + M[3]*B1,
		- M[12]*A5 + M[14]*A2 - M[15]*A1,
		+ M[8]*A5 - M[10]*A2 + M[11]*A1,
		+ M[4]*B4 - M[5]*B2 + M[7]*B0,
		- M[0]*B4 + M[1]*B2 - M[3]*B0,
		+ M[12]*A4 - M[13]*A2 + M[15]*A0,
		- M[8]*A4 + M[9]*A2 - M[11]*A0,
		- M[4]*B3 + M[5]*B1 - M[6]*B0,
		+ M[0]*B3 - M[1]*B1 + M[2]*B0,
		- M[12]*A3 + M[13]*A1 - M[14]*A0,
		+ M[8]*A3 - M[9]*A1 + M[10]*A0
	);
}

Matrix44 Matrix44::inverse() const
{
	float det = determinant();
	//if determinant is zero then reutrn zero matrix
	if(Math::isZero(det))
	{
		return Matrix44::ZERO;
	}
	//compute the inverse by adjoint * reciprocal of determinant
	float invDet = Math::inverse(det);
	return adjoint() * invDet;
}

const Matrix44 Matrix44::rotate(const Angle &xAngle,const Angle &yAngle,const Angle &zAngle)
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

	return Matrix44
	(
		Cy*Cz, -Cy*Sz, Sy,0.0f,
		Sx*Sy*Cz + Cx*Sz, -Sx*Sy*Sz + Cx*Cz, -Sx*Cy,0.0f,
		-Cx*Sy*Cz + Sx*Sz, Cx*Sy*Sz + Sx*Cz, Cx*Cy,0.0f,
		0.0f,0.0f,0.0f,1.0f
	);
}

const Matrix44 Matrix44::rotateX(const Angle &angle)
{
	float a = angle.asRadians();
	return Matrix44
	(
		1.0f,0.0f,0.0f,0.0f,
		0.0f,Math::cos(a),-Math::sin(a),0.0f,
		0.0f,Math::sin(a),Math::cos(a),0.0f,
		0.0f,0.0f,0.0f,1.0f
	);
}

const Matrix44 Matrix44::rotateY(const Angle &angle)
{
	float a = angle.asRadians();
	return Matrix44
	(
		Math::cos(a),0.0f,Math::sin(a),0.0f,
		0.0f,1.0f,0.0f,0.0f,
		-Math::sin(a),0.0f,Math::cos(a),0.0f,
		0.0f,0.0f,0.0f,1.0f
	);
}

const Matrix44 Matrix44::rotateZ(const Angle &angle)
{
	float a = angle.asRadians();
	return Matrix44
	(
		Math::cos(a),-Math::sin(a),0.0f,0.0f,
		Math::sin(a),Math::cos(a),0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	);
}

const Matrix44 Matrix44::translate(float x,float y,float z)
{
	return Matrix44
	(
		1.0f,0.0f,0.0f,x,
		0.0f,1.0f,0.0f,y,
		0.0f,0.0f,1.0f,z,
		0.0f,0.0f,0.0f,1.0f
	);
}

const Matrix44 Matrix44::scale(float x,float y,float z)
{
	return Matrix44
	(
		x,0.0f,0.0f,0.0f,
		0.0f,y,0.0f,0.0f,
		0.0f,0.0f,z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	);
}

#ifdef DEBUG
void Matrix44::test()
{
	std::cout << "Matrix44 tests" << std::endl;
	std::cout << "Stream test (identity matrix): " << std::endl << Matrix44::IDENTITY << std::endl;
	std::cout << "Scale matrix of 3: " << std::endl << Matrix44::IDENTITY * 3.0f << std::endl;
	std::cout << "Inverse of scale matrix (3): " << std::endl << (Matrix44::IDENTITY * 3.0f).inverse() << std::endl;
	Matrix44 a(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16),b(17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32);
	std::cout << "Matrix A: " << std::endl << a << std::endl;
	std::cout << "Matrix B: " << std::endl << b << std::endl;
	std::cout << "Index test on matrix A:\n";
	for(int i=0; i<16; i++)
	{
		std::cout << "\tIndex " << i << ": " << a[i] << std::endl;
	}
	std::cout << "Inverse of matrix A: " << std::endl << a.inverse() << std::endl;
	std::cout << "Matrix A * its inverse should give identity: " << std::endl << a * a.inverse() << std::endl;

	//test rotation matrix
	float angle = 45.0f * Math::DEG_TO_RAD;
	Matrix44 rotation = Matrix44::rotate(angle,angle,angle);
	Vector3 v = Vector3::X_AXIS;

	std::cout << "Vector to transform: " << v << std::endl;
	std::cout << "Rotation matrix (45 degrees): " << std::endl << rotation << std::endl;
	std::cout << "Transformation of vector by matrix: " << rotation * v << std::endl;

	std::cout << std::endl << Matrix44(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16) * Vector3(17,18,19) << std::endl;

	std::cout << "testing (r,c) access (zero indexed): " << std::endl;
	std::cout << a << std::endl;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			std::cout << "\a(" << i << ',' << j << "): " << a(i,j) << std::endl;
		}
	}

	std::cout << "Testing static rotate(angle) with angle of 45 degrees on vector (1,0): " << std::endl;
	std::cout << Matrix44::rotate(45.0f * Math::DEG_TO_RAD,45.0f * Math::DEG_TO_RAD,45.0f * Math::DEG_TO_RAD) * Vector3::X_AXIS << std::endl;

	//test angle
	std::cout << "Rotation matrix with Angle class holding 45.0f as Angle::DEGREES: " << std::endl;
	std::cout << Matrix44::rotate(Angle(45.0f,Angle::DEGREES),Angle(45.0f,Angle::DEGREES),Angle(45.0f,Angle::DEGREES)) << std::endl;
	std::cout << "Rotation matrix with Angle class holding Math::PI / 4 as Angle::RADIANS: " << std::endl;
	std::cout << Matrix44::rotate(Angle(Math::PI / 4.0f),Angle(Math::PI / 4.0f),Angle(Math::PI / 4.0f)) << std::endl;

	std::cout << Matrix44::rotate(Angle(45.0f,Angle::DEGREES),Angle(45.0f,Angle::DEGREES),Angle(45.0f,Angle::DEGREES)) * Vector3(0.5f,0.5f,0.5f) << std::endl;

	std::cout << std::endl;

	Matrix44 Rx = Matrix44::rotateX(Angle(10,Angle::DEGREES));
	Matrix44 Ry = Matrix44::rotateY(Angle(20,Angle::DEGREES));
	Matrix44 Rz = Matrix44::rotateZ(Angle(30,Angle::DEGREES));
	Matrix44 Rxyz = Matrix44::rotate
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

	Matrix44 p = (Rxyz * Rxyz.inverse());
	p.clean();
	std::cout << p << std::endl;

	//test determinant

	std::cout << std::endl;
}
#endif

}
