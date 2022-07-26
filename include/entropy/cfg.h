#ifndef __entropyCfg_h__
#define __entropyCfg_h__

//std dependencies
#include <cstdlib> //must be included before GLUT
#include <assert.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>

//GLUT dependencies
#include <gl/glut.h>

namespace entropy
{

//typedefs
typedef std::string String;

}

//temp
#define DEBUG

#ifdef DEBUG
	#define ASSERT(x) assert(x)
#else
	#define ASSERT(x)
#endif

#endif
