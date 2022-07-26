#ifndef __marchingCubes_h__
#define __marchingCubes_h__

//local dependencies
#include <entropy\mesh\mesh.h>
#include <entropy\math\r3\point3.h>
#include <entropy\math\r3\vector3.h>
#include <entropy\math\r3\normal3.h>

#include <entropy\color\color.h>

namespace entropy
{

//Implements the marching cubes algorithm, which generates
//a mesh given an implicit function.
//To use the marching cubes implementation, it is required
//that one derive a class from ImplicitFunction and fill
//the compute method. MarchingCubes takes this in its march call.
class MarchingCubes
{
public:
	struct Vertex
	{
		Point3 position;
		Vector3 normal;
		float isoValue; //value of function at this vertex
	};
	struct SurfaceVertex
	{
		Point3 position;
		Normal3 normal;
	};
	struct Voxel
	{
		Vertex vertices[8]; //vertices of a voxel
	};
	//Abstract base class that implements an implicit function.
	class ImplicitFunction
	{
	public:
		//Compute the function at point p.
		virtual float compute(const Point3 &p) = 0;
	};
	//constructor
	MarchingCubes(float width=1.0f,unsigned dimension=1);
	//destructor
	~MarchingCubes();
	//methods
	void rebuild(float width,unsigned dimension);
	void freeMemory();
	//Run the algorithm. Returns a filled in mesh if successful.
	Mesh *march(ImplicitFunction *f,float isoLevel=0.0f);
	//for debugging
	void render();
private:
	//methods
	Point3 vertexInterpolate(float isoLevel,const Point3 &v1,const Point3 &v2,float isoV1,float isoV2);
	void buildVoxelGrid(unsigned dimension);
	//static variables
	static const int edgeTable[256];		//edge lookup table
	static const int triTable[256][16];		//triangle lookup table
	static const int interpTable[12][2];	//interp lookup table
	//variables
	float width;
	Voxel *voxels;
	unsigned numVoxels;

	unsigned DIMENSION; //TEMP

protected:
	//
};

//a set of useful marching cube functions
class MC_Sphere : public MarchingCubes::ImplicitFunction
{
public:
	//constructor
	MC_Sphere(const Point3 &center,float radius) : center(center),radiusSq(radius*radius) {}
	//methods
	virtual float compute(const Point3 &p);
private:
	Point3 center;
	float radiusSq;
};

}

#endif
