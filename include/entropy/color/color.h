#ifndef __color3_h__
#define __color3_h__

//local dependencies
#include <entropy\cfg.h>

namespace entropy
{

class Color
{
public:
	//constructors
	Color() : r(0.0f),g(0.0f),b(0.0f) {}
	Color(float _r,float _g,float _b) : r(_r),g(_g),b(_b) {}
	Color(const Color &right);
	//destructor
	~Color() {}
	//operator overloads
	Color &operator=(const Color &c);
	operator float*();
	float &operator[](int i);
	Color operator+(const Color &c) const;
	Color operator+=(const Color &c);
	Color operator-() const;
	Color operator-(const Color &c) const;
	Color operator-=(const Color &c);
	Color operator*(float scalar) const;
	Color &operator*=(float scalar);
	Color operator/(float scalar) const;
	Color &operator/=(float scalar);
	bool operator==(const Color &c) const;
	bool operator!=(const Color &c) const;
	//friend operators
	friend std::ostream &operator<<(std::ostream &out,const Color &c);
	//methods

	//TODO

	//static methods
	#ifdef DEBUG
	static void test();
	#endif
	//static variables
	static const Color RED,GREEN,BLUE,BLACK,WHITE;
	//variables
	float r,g,b;
private:
	//
protected:
	//
};

}

#endif
