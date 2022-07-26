#ifndef __mesh_h__
#define __mesh_h__

//local dependencies
#include <entropy\cfg.h>
#include <entropy\math\math.h>
#include <entropy\math\r3\vector3.h>

namespace entropy
{

//forward declarations - for friend classes
class MarchingCubes;

class Mesh
{
public:
	//friend classes
	friend MarchingCubes;
	struct Vertex
	{
		Vertex() : x(0.0f),y(0.0f),z(0.0f) {}
		Vertex(float x,float y,float z) : x(x),y(y),z(z) {}
		float x,y,z;
	};
	struct Normal
	{
		Normal() : x(0.0f),y(0.0f),z(0.0f) {}
		Normal(float x,float y,float z) : x(x),y(y),z(z) {}
		float x,y,z;
	};
	struct Triangle
	{
		Triangle() {}
		Triangle(const Vertex &v0,const Vertex &v1,const Vertex &v2) : v0(v0),v1(v1),v2(v2) {}
		Vertex v0,v1,v2;
		Normal n;
	};
	//methods
	void weldVertices(float tolerance=Math::EPSILON);
	void constructNormals();
	bool readObj(const String &filePath);
	bool writeObj(const String &filePath);
	//for debugging
	void render(bool wire);
	//static variables
	static const Mesh EMPTY;
private:
	//variables
	std::vector<Vertex> vertices;
	std::vector<Normal> normals;
	std::vector<Triangle> triangles;
	std::vector<unsigned> triangle_indices;
protected:
	//
};

}

#endif
