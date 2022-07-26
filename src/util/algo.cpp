//local dependencies
#include <entropy\util\algo.h>

namespace entropy
{

#ifdef DEBUG
void Algo::test()
{
	std::cout << "Algo test" << std::endl;

	float A = 3.333;
	float B = 1.111;
	std::cout << "A: " << A << std::endl;
	std::cout << "B: " << B << std::endl;
	std::cout << "Test swap, swap A with B" << std::endl;
	Algo::swap<float>(A,B);
	std::cout << "New A: " << A << std::endl;
	std::cout << "New B: " << B << std::endl;

	std::cout << "Test swap with pointers (note changed values of A and B)..." << std::endl;
	A = 5.555;
	B  = 9.999;
	float *pA = &A;
	float *pB = &B;
	std::cout << "A: " << A << std::endl;
	std::cout << "B: " << B << std::endl;
	Algo::swap<float>(A,B);
	std::cout << "New A: " << A << std::endl;
	std::cout << "New B: " << B << std::endl;

	std::cout << std::endl;
}
#endif

}
