//local dependencies
#include <entropy\mesh\mesh.h>
#include <entropy\cfg.h>
#include <entropy\math\r3\point3.h>

namespace entropy
{

//static variable definitions
const Mesh Mesh::EMPTY;

void Mesh::weldVertices(float tolerance)
{
	std::vector<Mesh::Vertex> old_vertices;
	std::vector<unsigned> remaining; //remaining vertex indices to process from old_vertices

	for(unsigned i=0; i<vertices.size(); i++)
	{
		old_vertices.push_back(vertices[i]);
		remaining.push_back(i);
	}

	vertices.clear();

	Point3 init,p,weld;
	unsigned weldCount;
	std::vector<unsigned> shared_tri_indices;
	std::vector<unsigned>::iterator i;

	while(remaining.size() > 0)
	{
		i = remaining.begin();

		//save this point
		init = Point3(old_vertices[*i].x,old_vertices[*i].y,old_vertices[*i].z);
		weld = init;
		weldCount = 1;

		shared_tri_indices.push_back(*i); //save this index

		//remove this element
		i = remaining.erase(i);

		//now carry on
		while(i != remaining.end())
		{
			p = Point3(old_vertices[*i].x,old_vertices[*i].y,old_vertices[*i].z);
			//check distance
			if(p.distance(init) <= tolerance)
			{
				//add to weld point
				weld += p;
				weld *= 0.5; //average it
				weldCount++;

				shared_tri_indices.push_back(*i); //save triangle index

				//remove this index
				i = remaining.erase(i);

				if(i == remaining.end())
				{
					break;
				}
			}
			i++; //check next vertex
		}

		//save new vertex (in this case, if no weld points
		//this will just be the original point ie. init).
		vertices.push_back(Mesh::Vertex(weld.x,weld.y,weld.z));

		//set shared triangle indices
		for(unsigned t=0; t<triangles.size(); t++)
		{
			for(unsigned u=0; u<shared_tri_indices.size(); u++)
			{
				for(unsigned v=0; v<3; v++)
				{
					if(triangles[t].v[v] == shared_tri_indices[u])
					{
						//std::cout << "got shared vertices... for index " << vertices.size()-1 << std::endl;
						triangles[t].v[v] = vertices.size()-1;
					}
				}
			}
		}
		shared_tri_indices.clear();

		//restart loop
		continue;
	}

	std::cout << "# vertices = " << vertices.size() << std::endl;
	for(unsigned i=0; i<vertices.size(); i++)
	{
		std::cout << "# " << i << ":\t" << vertices[i].x << ' ' << vertices[i].y << ' ' << vertices[i].z << std::endl;
	}
	std::cout << "# triangles = " << triangles.size() << std::endl;
	for(unsigned i=0; i<triangles.size(); i++)
	{
		std::cout << "Triangle #" << i << ":\n";
		for(unsigned v=0; v<3; v++)
		{
			std::cout << vertices[triangles[i].v[v]].x << ' ' << vertices[triangles[i].v[v]].y << ' ' << vertices[triangles[i].v[v]].z << std::endl;
		}
	}

	old_vertices.clear();
}

void Mesh::constructNormals()
{
	for(unsigned int i=0; i<triangles.size(); i++)
	{
		Vector3 v0(vertices[triangles[i].v[0]].x,vertices[triangles[i].v[0]].y,vertices[triangles[i].v[0]].z);
		Vector3 v1(vertices[triangles[i].v[1]].x,vertices[triangles[i].v[1]].y,vertices[triangles[i].v[1]].z);
		Vector3 v2(vertices[triangles[i].v[2]].x,vertices[triangles[i].v[2]].y,vertices[triangles[i].v[2]].z);

		Vector3 n = (v1 - v0).cross(v2 - v0);
		n.normalize();
		n *= 0.25f;

		triangles[i].n = i; //save normal index
		normals.push_back
		(
			Mesh::Normal(n.x,n.y,n.z)
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

	for(unsigned int i=0; i<vertices.size(); i++)
	{
		out << "v " << vertices[i].x << ' ' << vertices[i].y << ' ' << vertices[i].z << std::endl;
	}

	//indices start at 1
	for(unsigned int i=0; i<triangles.size(); i++)
	{
		out << "f " << triangles[i].v[0]+1 << ' ' << triangles[i].v[1]+1 << ' ' << triangles[i].v[2]+1 << std::endl;
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
			Vector3 v0(vertices[triangles[i].v[0]].x,vertices[triangles[i].v[0]].y,vertices[triangles[i].v[0]].z);
			Vector3 v1(vertices[triangles[i].v[1]].x,vertices[triangles[i].v[1]].y,vertices[triangles[i].v[1]].z);
			Vector3 v2(vertices[triangles[i].v[2]].x,vertices[triangles[i].v[2]].y,vertices[triangles[i].v[2]].z);
			Vector3 c = (v0 + v1 + v2) / 3.0f;

			//draw triangle centers
			glColor3f(0,1,0);
			glBegin(GL_POINTS);
			glVertex3f(c.x,c.y,c.z);
			glEnd();

			//draw triangle normals
			if(normals.size() > 0)
			{
				glColor3f(1,0,0);
				glBegin(GL_LINES);
				glVertex3f(c.x,c.y,c.z);
				glVertex3f
				(
					c.x + normals[triangles[i].n].x,
					c.y + normals[triangles[i].n].y,
					c.z + normals[triangles[i].n].z
				);
				glEnd();
			}

			//draw triangles
			glColor3f(1,1,1);
			glBegin(GL_LINE_LOOP);
		}
		else
		{
			glEnable(GL_LIGHTING);
			glBegin(GL_TRIANGLES);
		}
		glNormal3f
		(
			normals[triangles[i].n].x,
			normals[triangles[i].n].y,
			normals[triangles[i].n].z
		);
		glVertex3f(vertices[triangles[i].v[0]].x,vertices[triangles[i].v[0]].y,vertices[triangles[i].v[0]].z);
		glVertex3f(vertices[triangles[i].v[1]].x,vertices[triangles[i].v[1]].y,vertices[triangles[i].v[1]].z);
		glVertex3f(vertices[triangles[i].v[2]].x,vertices[triangles[i].v[2]].y,vertices[triangles[i].v[2]].z);
		glEnd();

		glDisable(GL_LIGHTING);
	}
	glPointSize(1.0f);
}

}
