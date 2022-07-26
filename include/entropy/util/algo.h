#ifndef __algo_h__
#define __algo_h__

//local dependencies
#include <entropy\cfg.h>

namespace entropy
{

class Algo
{
public:
	//methods
	template<typename T> static void swap(T &a,T &b);
	//static methods
	#ifdef DEBUG
	static void test();
	#endif
private:
	//
protected:
	//
};

//swap a and b
template<typename T>
void Algo::swap(T &a,T &b)
{
	T tmp = b;
	b = a;
	a = tmp;
}

}

#endif
