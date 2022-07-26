//local dependencies
#include <entropy\mesh\mesh.h>
#include <entropy\cfg.h>

#include <entropy\math\r3\vector3.h>

namespace entropy
{

//static variable definitions
const Mesh Mesh::EMPTY;

void Mesh::weldVertices(float tolerance)
{
	std::vector<Vertex> vertices_copy;
	for(unsigned i=0; i<vertices.size(); i++)
	{
		vertices_copy[i] = vertices[i];
	}
	//clear vertices
	vertices.clear();
}

void Mesh::constructNormals()
{
	for(unsigned int i=0; i<triangles.size(); i++)
	{
		Vector3 v0(triangles[i].v0.x,triangles[i].v0.y,triangles[i].v0.z);
		Vector3 v1(triangles[i].v1.x,triangles[i].v1.y,triangles[i].v1.z);
		Vector3 v2(triangles[i].v2.x,triangles[i].v2.y,triangles[i].v2.z);

		Vector3 n = (v1 - v0).cross(v2 - v0);
		n.normalize();
		n *= 0.25f;

		triangles[i].n = Mesh::Normal
		(
			n.x,n.y,n.z
		);
	}
}

//reads an obj file
bool Mesh::readObj(const String &filePath)
{
	std::ifstream in(filePath.c_str());
	if(!in.is_open())
	{
		return false;
	}

	//read file
	return false; //YET TO IMP

	in.close();

	return true;
}

//outputs a very simple obj file that just contains
//vertex and face info.
bool Mesh::writeObj(const String &filePath)
{
	std::ofstream out(filePath.c_str());
	if(!out.is_open())
	{
		return false;
	}

	for(unsigned int i=0; i<triangles.size(); i++)
	{
		out << "v " << triangles[i].v0.x << ' ' << triangles[i].v0.y << ' ' << triangles[i].v0.z << std::endl;
		out << "v " << triangles[i].v1.x << ' ' << triangles[i].v1.y << ' ' << triangles[i].v1.z << std::endl;
		out << "v " << triangles[i].v2.x << ' ' << triangles[i].v2.y << ' ' << triangles[i].v2.z << std::endl;
	}

	int index = 0;
	for(unsigned int i=0; i<triangles.size(); i++)
	{
		out << "f " << index+1 << ' ' << index+2 << ' ' << index+3 << std::endl;
		index += 3;
	}

	out.close();

	return true;
}

void Mesh::render(bool wire)
{
	glPointSize(3.0f);
	for(unsigned int i=0; i<triangles.size(); i++)
	{
		if(wire)
		{
			//get triangle center
			Vector3 v0(triangles[i].v0.x,triangles[i].v0.y,triangles[i].v0.z);
			Vector3 v1(triangles[i].v1.x,triangles[i].v1.y,triangles[i].v1.z);
			Vector3 v2(triangles[i].v2.x,triangles[i].v2.y,triangles[i].v2.z);
			Vector3 c = (v0 + v1 + v2) / 3.0f;

			//draw triangle centers
			glColor3f(0,1,0);
			glBegin(GL_POINTS);
			glVertex3f(c.x,c.y,c.z);
			glEnd();

			//draw triangle normals
			glColor3f(1,0,0);
			glBegin(GL_LINES);
			glVertex3f(c.x,c.y,c.z);
			glVertex3f
			(
				c.x + triangles[i].n.x,
				c.y + triangles[i].n.y,
				c.z + triangles[i].n.z
			);
			glEnd();

			//draw triangles
			glColor3f(1,1,1);
			glBegin(GL_LINE_LOOP);
		}
		else
		{
			glEnable(GL_LIGHTING);
			glBegin(GL_TRIANGLES);
		}
		glNormal3f(triangles[i].n.x,triangles[i].n.y,triangles[i].n.z);
		glVertex3f(triangles[i].v0.x,triangles[i].v0.y,triangles[i].v0.z);
		glVertex3f(triangles[i].v1.x,triangles[i].v1.y,triangles[i].v1.z);
		glVertex3f(triangles[i].v2.x,triangles[i].v2.y,triangles[i].v2.z);
		glEnd();

		glDisable(GL_LIGHTING);
	}
	glPointSize(1.0f);
}

}
