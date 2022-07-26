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
		Triangle(unsigned v0,unsigned v1,unsigned v2)
		{
			v[0] = v0;
			v[1] = v1;
			v[2] = v2;
		}
		unsigned v[3]; //vertex indices
		unsigned n; //normal index
	};
	//methods
	void printInfo()
	{
		std::cout << "# vertices:\t" << vertices.size() << std::endl;
		std::cout << "# triangles:\t" << triangles.size() << std::endl;
		std::cout << "# normals:\t" << normals.size() << std::endl;
		std::cout << std::endl;
		for(unsigned i=0; i<triangles.size(); i++)
		{
			std::cout << "triangle " << i+1 << ":\n";
			std::cout << '(' << vertices[triangles[i].v[0]].x << ' ' << vertices[triangles[i].v[0]].y << ' ' << vertices[triangles[i].v[0]].z << "),";
			std::cout << '(' << vertices[triangles[i].v[1]].x << ' ' << vertices[triangles[i].v[1]].y << ' ' << vertices[triangles[i].v[1]].z << "),";
			std::cout << '(' << vertices[triangles[i].v[2]].x << ' ' << vertices[triangles[i].v[2]].y << ' ' << vertices[triangles[i].v[2]].z << ")\n";
		}
		
		for(unsigned i=0; i<vertices.size(); i++)
		{
			std::cout << "# " << i << ' ' << vertices[i].x << ' ' << vertices[i].y << ' ' << vertices[i].z << std::endl;
		}
	}
	void weldVertices(float tolerance=Math::EPSILON);
	void constructNormals();
	bool readObj(const String &filePath);
	bool writeObj(const String &filePath);
	//for debugging
	void render(bool wire);
	//static variables
	static const Mesh EMPTY;
//private:
	//variables
	std::vector<Mesh::Vertex> vertices;
	std::vector<Mesh::Normal> normals;
	std::vector<Mesh::Triangle> triangles;
protected:
	//
};

}

#endif
