//local dependencies
#include <entropy\util\noise3D.h>
#include <entropy\math\math.h>

namespace entropy
{

//static forward definitions
const Vector3 Noise3D::grad[16] =
{
	Vector3(1,1,0),
	Vector3(-1,1,0),
	Vector3(1,-1,0),
	Vector3(-1,-1,0),
	Vector3(1,0,1),
	Vector3(-1,0,1),
	Vector3(1,0,-1),
	Vector3(-1,0,-1),
	Vector3(0,1,1),
	Vector3(0,-1,1),
	Vector3(0,1,-1),
	Vector3(0,-1,-1),
	Vector3(1,1,0),
	Vector3(-1,1,0),
	Vector3(0,-1,1),
	Vector3(0,-1,-1)
};

Noise3D::Noise3D()
{
	for(int i=0; i<16; i++)
	{
		phi[i] = i;
	}
	//shuffle phi
	for(int i=14; i>=0; i--)
	{
		int target = (int)(Math::random(1.0f) * i);
		int temp = phi[i+1];
		phi[i+1] = phi[target];
		phi[target] = temp;
	}
}

float Noise3D::noise(const Vector3 &p) const
{
	int fi,fj,fk;
	float fu,fv,fw,sum;
	Vector3 v;

	fi = (int)Math::floor(p.x);
	fj = (int)Math::floor(p.y);
	fk = (int)Math::floor(p.z);
	fu = p.x - (float)fi;
	fv = p.y - (float)fj;
	fw = p.z - (float)fk;
	sum = 0.0f;

	v = Vector3(fu,fv,fw);
	sum += knot(fi,fj,fk,v);

	v = Vector3(fu - 1,fv,fw);
	sum += knot(fi + 1,fj,fk,v);

	v = Vector3(fu,fv - 1,fw);
	sum += knot(fi,fj + 1,fk,v);

	v = Vector3(fu,fv,fw - 1);
	sum += knot(fi,fj,fk + 1,v);

	v = Vector3(fu - 1,fv - 1,fw);
	sum += knot(fi + 1,fj + 1,fk,v);

	v = Vector3(fu - 1,fv,fw - 1);
	sum += knot(fi + 1,fj,fk + 1,v);

	v = Vector3(fu,fv - 1,fw - 1);
	sum += knot(fi,fj + 1,fk + 1,v);

	v = Vector3(fu - 1,fv - 1,fw - 1);
	sum += knot(fi + 1,fj + 1,fk + 1,v);

	return sum;
}

float Noise3D::turbulence(const Vector3 &p,int depth) const
{
	float sum = 0.0f;
	float weight = 1.0f;
	Vector3 ptemp(p);

	sum = Math::abs(noise(ptemp));

	for(int i=1; i<depth; i++)
	{
		weight = weight * 2;
		ptemp = p * weight;
		sum += Math::abs(noise(ptemp)) / weight;
	}

	return sum;
}

float Noise3D::dturbulence(const Vector3 &p,int depth,float d) const
{
	float sum = 0.0f;
	float weight = 1.0f;
	Vector3 ptemp(p);

	sum = Math::abs(noise(ptemp));

	for(int i=1; i<depth; i++)
	{
		weight = weight * d;
		ptemp = p * weight;
		sum += Math::abs(noise(ptemp)) / d;
	}

	return sum;
}

float Noise3D::omega(float t) const
{
	t = (t > 0.0f) ? t : -t;
	//we can assume that t is in [-1,1]
	return (-6.0f * Math::pow(t,6) + (15.0f * Math::pow(t,4)) - (10.0f * Math::pow(t,3)) + 1.0f);
}

Vector3 Noise3D::gamma(int i,int j,int k) const
{
	int idx;
	idx = phi[(int)Math::abs(k) % 16];
	idx = phi[(int)Math::abs(j + idx) % 16];
	idx = phi[(int)Math::abs(i + idx) % 16];
	return grad[idx];
}

int Noise3D::intGamma(int i,int j) const
{
	int idx;
	idx = phi[(int)Math::abs(j) % 16];
	idx = phi[(int)Math::abs(i + idx) % 16];
	return idx;
}

float Noise3D::knot(int i,int j,int k,Vector3 &v) const
{
	return omega(v.x) * omega(v.y) * omega(v.z) * gamma(i,j,k).dot(v);
}

}
