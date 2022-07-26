#ifndef __math_h__
#define __math_h__

//local dependencies
#include <entropy\cfg.h>

namespace entropy
{

class Math
{
	public:
		enum QUADRATIC_ROOTS
		{
			NON_EQUAL_ROOTS, //two roots
			EQUAL_ROOTS, //one root
			NO_ROOTS
		};
		//static methods
		static const float abs(float v);
		static const float min(float a,float b);
		static const float max(float a,float b);
		static const bool isZero(float v);
		static const float inverse(float v);
		static const float sqrt(float v);
		static const float inverseSqrt(float v);
		static const float sin(float v);
		static const float aSin(float v);
		static const float cos(float v);
		static const float aCos(float v);
		static void sinCos(float v,float &s,float &c);
		static const float tan(float v);
		static const float aTan(float v);
		static const float aTan2(float y,float x);
		static const float floor(float v);
		static const float ceil(float v);
		static const float exp(float v);
		static const float pow(float a,float b);
		static const float mod(float a,float b);
		static const float random(float max);
		static const float randomBinomial(float max = 1.0f);
		static const float lerp(float t,float a,float b);
		template<typename T> static const T lerp(float t,const T &a,const T &b);
		static const float clamp(float v,float a,float b);
		static const QUADRATIC_ROOTS quadratic(float a,float b,float c,float *t0,float *t1);
		//test
		#ifdef DEBUG
		static void test();
		#endif
		//static variables
		static const float MIN;
		static const float MAX;
		static const float EPSILON;
		static const float RAY_EPSILON;
		static const float PI;
		static const float HALF_PI;
		static const float TWO_PI;
		static const float DEG_TO_RAD;
		static const float RAD_TO_DEG;
	private:
		//
	protected:
		//
};

template<typename T>
const T Math::lerp(float t,const T &a,const T &b)
{
	return (a * (1.0f - t)) + (b * t);
}

}

#endif
