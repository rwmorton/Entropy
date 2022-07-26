//local dependencies
#include <entropy\math\math.h>
#include <entropy\util\algo.h>

//std dependencies
#include <float.h>
#include <math.h>

namespace entropy
{

//static members
const float Math::MIN = FLT_MIN;
const float Math::MAX = FLT_MAX;
const float Math::EPSILON = 1.0e-6f;
const float Math::RAY_EPSILON = 1.0e-3f;
const float Math::PI = 3.1415926535897932384626433832795f;
const float Math::HALF_PI = 0.5f * Math::PI;
const float Math::TWO_PI = 2.0f * Math::PI;
const float Math::DEG_TO_RAD = Math::PI / 180.0f;
const float Math::RAD_TO_DEG = 180.0f / Math::PI;

const float Math::abs(float v)
{
	return ::fabsf(v);
}

const float Math::min(float a,float b)
{
	return (a < b ? a : b);
}

const float Math::max(float a,float b)
{
	return (a > b ? a : b);
}

const bool Math::isZero(float v)
{
	return Math::abs(v) < Math::EPSILON;
}

const float Math::inverse(float v)
{
	ASSERT(!Math::isZero(v));
	return 1.0f / v;
}

const float Math::sqrt(float v)
{
	return ::sqrtf(v);
}

const float Math::inverseSqrt(float v)
{
	return Math::inverse(::sqrtf(v));
}

const float Math::sin(float v)
{
	return ::sinf(v);
}

//returns range [-n/2,n/2] radians
const float Math::aSin(float v)
{
	return ::asinf(v);
}

const float Math::cos(float v)
{
	return ::cosf(v);
}

//domain [-1,1]
//returns range [-n,n] radians
const float Math::aCos(float v)
{
	return ::acosf(v);
}

void Math::sinCos(float v,float &s,float &c)
{
	s = ::sinf(v);
	c = ::cosf(v);
}

const float Math::tan(float v)
{
	return ::tanf(v);
}

//returns range [-n/2,n/2] radians
const float Math::aTan(float v)
{
	return ::atanf(v);
}

//arc tangent of y/x
//returns range [-n,n] radians
const float Math::aTan2(float y,float x)
{
	return ::atan2f(y,x);
}

const float Math::floor(float v)
{
	return ::floorf(v);
}

const float Math::ceil(float v)
{
	return ::ceilf(v);
}

const float Math::exp(float v)
{
	return ::expf(v);
}

const float Math::pow(float a,float b)
{
	return ::powf(a,b);
}

const float Math::mod(float a,float b)
{
	return ::fmodf(a,b);
}

const float Math::random(float max)
{
	return max * (float(::rand()) / RAND_MAX);
}

const float Math::randomBinomial(float max)
{
	return random(max) - random(max);
}

const float Math::lerp(float t,float a,float b)
{
	return (1.0f - t) * a + t * b;
}

//clamp v to range [a,b]
const float Math::clamp(float v,float a,float b)
{
	if(v < a)
	{
		return a;
	}
	else if(v > b)
	{
		return b;
	}
	return v;
}

const Math::QUADRATIC_ROOTS Math::quadratic(float a,float b,float c,float *t0,float *t1)
{
	//calculate the discriminant
	float discrim = b*b - (4 * a * c);

	if(Math::isZero(discrim))
	{
		//single root
		float sqRootOfDiscrim = Math::sqrt(discrim);
		*t0 = (-b + sqRootOfDiscrim) / (2 * a);
		*t1 = (-b - sqRootOfDiscrim) / (2 * a);
		if(*t0 > *t1)
		{
			Algo::swap<float>(*t0,*t1);
		}
		return Math::EQUAL_ROOTS;
	}
	if(discrim > Math::EPSILON)
	{
		//two roots
		float sqRootOfDiscrim = Math::sqrt(discrim);
		*t0 = (-b + sqRootOfDiscrim) / (2 * a);
		*t1 = (-b - sqRootOfDiscrim) / (2 * a);
		if(*t0 > *t1)
		{
			Algo::swap<float>(*t0,*t1);
		}
		return Math::NON_EQUAL_ROOTS;
	}
	else
	{
		//complex roots
		return Math::NO_ROOTS;
	}
}

//test
#ifdef DEBUG
void Math::test()
{
	std::cout << "Math tests" << std::endl;
	std::cout << "Math::abs(-2.35) -> should return 2.35: " << Math::abs(-2.35f) << std::endl;
	std::cout << "Math::min(-1,2) -> should return -1: " << Math::min(-1,2) << std::endl;
	std::cout << "Math::max(3,3.01) -> should return 3.01: " << Math::max(3,3.01f) << std::endl;
	std::cout << "Math::isZero(0) -> should return 1: " << Math::isZero(0) << std::endl;
	std::cout << "Math::isZero(0.00001) -> should return 0: " << Math::isZero(0.00001f) << std::endl;
	std::cout << "Math::isZero(0.000001) -> should return 0: " << Math::isZero(0.000001f) << std::endl;
	std::cout << "Math::isZero(0.0000001) -> should return 1: " << Math::isZero(0.0000001f) << std::endl;
	std::cout << "Math::inverse(2) -> should return 0.5: " << Math::inverse(2) << std::endl;
	std::cout << "Math::sqrt(4) -> should return 2: " << Math::sqrt(4) << std::endl;

	//get roots of x^2 - 1 -> roots are (-1,1)
	float t0,t1;
	float a = 1;
	float b = 0;
	float c = 1;
	std::cout << "solve quadratic: " << a << "x^2 + " << b << "x + " << c << std::endl;
	if(Math::quadratic(a,b,c,&t0,&t1) == Math::NO_ROOTS)
	{
		std::cout << "no roots" << std::endl;
	}
	else if(Math::quadratic(a,b,c,&t0,&t1) == Math::EQUAL_ROOTS)
	{
		std::cout << "single root: " << t0 << std::endl;
	}
	else if(Math::quadratic(a,b,c,&t0,&t1) == Math::NON_EQUAL_ROOTS)
	{
		std::cout << "two roots: " << t0 << ' ' << t1 << std::endl;
	}
	std::cout << std::endl;
}
#endif

}
