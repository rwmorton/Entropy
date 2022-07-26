#pragma warning(disable : 4996)

#include <conio.h>
#include <entropy\entropy.h>
using namespace entropy;

class RTApp : public App
{
public:
	RTApp()
	{
		shapes = new Sphere
		(
			Transform3::translate(3,0,0),false,1.0f
		);

		Vector3
		a
		(
			Math::randomBinomial(),
			Math::randomBinomial(),
			Math::randomBinomial()
		),
		b
		(
			Math::randomBinomial(),
			Math::randomBinomial(),
			Math::randomBinomial()
		),
		n
		(
			Math::randomBinomial(),
			Math::randomBinomial(),
			Math::randomBinomial()
		);
		std::cout << "a " << a << std::endl;
		std::cout << "b " << b << std::endl;
		std::cout << "n " << n << std::endl;
		std::cout << "n.a / n.b: " << n.dot(a) / n.dot(b) << std::endl;
		std::cout << "a / b: " << (a.x+a.y+a.z) / (b.x+b.y+b.z) << std::endl;

	}
	void Display()
	{
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(0,5,5,0,0,0,0,1,0);

		//draw shapes
		glColor3f(0.75,0.75,0.75);
		shapes->debug();

		//draw ray
		float tt = timer.getTotalTime();
		Ray3 r(Point3((Math::sin(tt) * 2) - 1,0,0),Vector3(1,Math::sin(tt) * 0.15f,Math::cos(tt) * 0.15f));
		GlUtil::drawRay(r,10.0f);

		DG dg;
		float tHit;
		if(shapes->intersect(r,&tHit,dg))
		{
			dg.debug();
		}

		App::DrawFPS();
		App::DrawGrid();
	}
	void Update()
	{
		App::Update();
	}
	void Key(unsigned char key)
	{
		switch(key)
		{
			case 27:
				exit(0);
		}
	}
private:
	Shape *shapes;
};

inline float Grad(int x, int y, int z, float dx, float dy, float dz);
inline float NoiseWeight(float t);
//perlin noise data
#define NOISE_PERM_SIZE 256
static int NoisePerm[2 * NOISE_PERM_SIZE] =
{
	151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96,
	53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142,
	// Rest of noise permutation table
	8, 99, 37, 240, 21, 10, 23,
	190,  6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
	88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168,  68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
	77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
	102, 143, 54,  65, 25, 63, 161,  1, 216, 80, 73, 209, 76, 132, 187, 208,  89, 18, 169, 200, 196,
	135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186,  3, 64, 52, 217, 226, 250, 124, 123,
	5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42,
	223, 183, 170, 213, 119, 248, 152,  2, 44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172, 9,
	129, 22, 39, 253,  19, 98, 108, 110, 79, 113, 224, 232, 178, 185,  112, 104, 218, 246, 97, 228,
	251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241,  81, 51, 145, 235, 249, 14, 239, 107,
	49, 192, 214,  31, 181, 199, 106, 157, 184,  84, 204, 176, 115, 121, 50, 45, 127,  4, 150, 254,
	138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180,
	151, 160, 137, 91, 90, 15,
	131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23,
	190,  6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
	88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168,  68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
	77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
	102, 143, 54,  65, 25, 63, 161,  1, 216, 80, 73, 209, 76, 132, 187, 208,  89, 18, 169, 200, 196,
	135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186,  3, 64, 52, 217, 226, 250, 124, 123,
	5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42,
	223, 183, 170, 213, 119, 248, 152,  2, 44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172, 9,
	129, 22, 39, 253,  19, 98, 108, 110, 79, 113, 224, 232, 178, 185,  112, 104, 218, 246, 97, 228,
	251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241,  81, 51, 145, 235, 249, 14, 239, 107,
	49, 192, 214,  31, 181, 199, 106, 157, 184,  84, 204, 176, 115, 121, 50, 45, 127,  4, 150, 254,
	138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
};

float Noise(float x, float y, float z)
{
	// Compute noise cell coordinates and offsets
	int ix = (int)Math::floor(x); //Floor2Int(x);
	int iy = (int)Math::floor(y); //Floor2Int(y);
	int iz = (int)Math::floor(z); //Floor2Int(z);
	float dx = x - ix, dy = y - iy, dz = z - iz;
	// Compute gradient weights
	ix &= (NOISE_PERM_SIZE-1);
	iy &= (NOISE_PERM_SIZE-1);
	iz &= (NOISE_PERM_SIZE-1);
	float w000 = Grad(ix,   iy,   iz,   dx,   dy,   dz);
	float w100 = Grad(ix+1, iy,   iz,   dx-1, dy,   dz);
	float w010 = Grad(ix,   iy+1, iz,   dx,   dy-1, dz);
	float w110 = Grad(ix+1, iy+1, iz,   dx-1, dy-1, dz);
	float w001 = Grad(ix,   iy,   iz+1, dx,   dy,   dz-1);
	float w101 = Grad(ix+1, iy,   iz+1, dx-1, dy,   dz-1);
	float w011 = Grad(ix,   iy+1, iz+1, dx,   dy-1, dz-1);
	float w111 = Grad(ix+1, iy+1, iz+1, dx-1, dy-1, dz-1);
	// Compute trilinear interpolation of weights
	float wx = NoiseWeight(dx);
	float wy = NoiseWeight(dy);
	float wz = NoiseWeight(dz);
	float x00 = Math::lerp(wx, w000, w100);
	float x10 = Math::lerp(wx, w010, w110);
	float x01 = Math::lerp(wx, w001, w101);
	float x11 = Math::lerp(wx, w011, w111);
	float y0 = Math::lerp(wy, x00, x10);
	float y1 = Math::lerp(wy, x01, x11);
	return Math::lerp(wz, y0, y1);
}
float Noise(const Vector3 &P)
{
	return Noise(P.x, P.y, P.z);
}
inline float Grad(int x, int y, int z, float dx,float dy, float dz)
{
 	int h = NoisePerm[NoisePerm[NoisePerm[x]+y]+z];
	h &= 15;
	float u = h<8 || h==12 || h==13 ? dx : dy;
	float v = h<4 || h==12 || h==13 ? dy : dz;
	return ((h&1) ? -u : u) + ((h&2) ? -v : v);
}
inline float NoiseWeight(float t)
{
	float t3 = t*t*t;
	float t4 = t3*t;
	return 6.f*t4*t - 15.f*t4 + 10.f*t3;
}

class MC_Test : public MarchingCubes::ImplicitFunction
{
public:
	virtual float compute(const Point3 &p)
	{
		//Vector2 xz(p.x,p.z);
		//xz = Transform2::rotate(Angle(450.0f,Angle::DEGREES))(xz);
		//return Noise(xz.x,p.y,xz.y);
		//return Noise(Vector3(Math::floor(Noise(p)),Noise(p),Noise(p)));

		return Noise(p);

		//return p.y;
	}
};

class MCApp : public App
{
private:
	MarchingCubes mc;
	float width;
	int resolution;
	Mesh *mesh;
	MarchingCubes::ImplicitFunction *f_sphere;
	bool showMC;
	bool wire;
public:
	MCApp(float w=1.5f) : mc(w,1),resolution(1),width(w),mesh(0),showMC(false),wire(true)
	{
		//f_sphere = new MC_Sphere(Point3::ZERO,1.0f);
		f_sphere = new MC_Test;

		//mesh = mc.march(f_sphere,0.0f);
		//mesh->printInfo();
		
		/*mesh = new Mesh;
		Mesh::Vertex
			v0(-1,0,-1),
			v1(-1,0,1),
			v2(-1,0,1),
			v3(1,0,-1),
			v4(1,0,-1),
			v5(1,0,1);
		mesh->vertices.push_back(v0);
		mesh->vertices.push_back(v1);
		mesh->vertices.push_back(v2);
		mesh->vertices.push_back(v3);
		mesh->vertices.push_back(v4);
		mesh->vertices.push_back(v5);
		Mesh::Triangle t0(0,1,3),t1(2,4,5);
		mesh->triangles.push_back(t0);
		mesh->triangles.push_back(t1);
		mesh->constructNormals();*/
	}
	void Update()
	{
		float t = timer.getFrameTime();

		if(mesh) delete mesh;
		mesh = mc.march(f_sphere,0.0f);
		mesh->constructNormals();

		//

		App::Update();
	}
	void Display()
	{
		glClearColor(.5,.5,.5,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		//gluLookAt(Math::sin(timer.getTotalTime()),Math::cos(timer.getTotalTime()),width *2,0,0,0,0,1,0);
		gluLookAt(2,2,2,0,0,0,0,1,0);

		glMatrixMode(GL_MODELVIEW);

		float spec[] = {1,1,1,1};
		float shin[] = {100};
		float lpos[] = {Math::sin(timer.getTotalTime()),Math::cos(timer.getTotalTime()),10,0};
		float lcol[] = {2,2,2,1};
		float amb[] = {0.1f,0.1f,0.1f,1.0f};
		glShadeModel(GL_SMOOTH);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shin);
		glLightfv(GL_LIGHT0,GL_POSITION,lpos);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,lcol);
		glLightfv(GL_LIGHT0,GL_SPECULAR,lcol);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);

		glColor3f(0,0,1);
		if(mesh) mesh->render(wire);

		glDisable(GL_LIGHTING);

		//
		if(showMC)
			mc.render();

		glPushMatrix();
		glRotatef(90.0f,1.0f,0.0f,0.0f);
		//App::DrawGrid();
		glPopMatrix();

		App::DrawFPS();

		glPopMatrix();
	}
	void Key(unsigned char key)
	{
		switch(key)
		{
			case '+':
				resolution++;
				mc.rebuild(width,resolution);
				break;
			case '-':
				resolution--;
				if(resolution < 0) resolution = 0;
				mc.rebuild(width,resolution);
				break;
			case '0':
				width += 0.1f;
				mc.rebuild(width,resolution);
				break;
			case '1':
				width -= 0.1f;
				if(width < 0.0f)
					width = 0.0f;
				mc.rebuild(width,resolution);
				break;
			case 'i':
				if(mesh)
				{
					//std::cout << "# triangles = " << mesh->triangles.size() << std::endl;
					//std::cout << "# vertices = " << mesh->vertices.size() << std::endl;
				}
				std::cout << Vector3::X_AXIS.cross(Vector3::Y_AXIS) << std::endl;
				std::cout << Vector3::Y_AXIS.cross(Vector3::X_AXIS) << std::endl;
				std::cout << Math::lerp(0.5f,2,3) << std::endl;
				break;
			case ']':
				showMC = !showMC;
				break;
			case 'w':
				wire = !wire;
				break;
			case 'f':
				//mesh->weldVertices(0.0001f);
				mesh->constructNormals();
				if(!mesh->writeObj("c:\\temp\\test.obj"))
				{
					std::cout << "error." << std::endl;
				}
				else
				{
					std::cout << "all done." << std::endl;
				}
				break;
			case 27:
				exit(0);
		}
	}
};

int main(int argc,char **argv)
{
	App *app = new MCApp; //new RTApp;
	GLUTWrapper::SetApplication(app);
	GLUTWrapper::Run(argc,argv);

	while(!kbhit()) ;

	return 0;
}
