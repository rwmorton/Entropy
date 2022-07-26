//std dependencies
#include <string>
#include <sstream>

//GLUT dependencies
#include <gl/glut.h>

//local dependencies
#include <entropy\app\App.h>

namespace entropy
{

App::App() : width(800),height(600),cachedFPS(0.0f),timeStep(0.0f),fpsUpdate(0.1f) {}

App::~App()
{
	Deinitialize();
}

const int App::GetWidth() const { return width; }

void App::SetWidth(int width) { this->width = width; }

const int App::GetHeight() const { return height; }

void App::SetHeight(int height) { this->height = height; }

const char *App::GetTitle()
{
	return "Entropy";
}

void App::InitializeGraphics()
{
	glClearColor(0.5f,0.5f,0.5f,1.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	SetView();
}

void App::SetView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,(double)width/(double)height,1.0,500.0);
	glMatrixMode(GL_MODELVIEW);
}

void App::Deinitialize() {}

void App::Display()
{
    // Clear the viewport and set the camera direction
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	gluLookAt(0.0f,5.0f,10.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);

	//draw simple cube
	glColor3f(0,0,1);
	glPushMatrix();
	glutWireCube(5);
	glPopMatrix();

	//draw the grid and FPS
	glColor3f(1,1,1);
	DrawGrid();
	DrawFPS();
}

void App::Update()
{
	//update timer
	timer.update();

	//refresh the display
	glutPostRedisplay();
}

void App::Key(unsigned char key) {}

void App::Resize(int width,int height)
{
	if(height <= 0)
	{
		height = 1;
	}
	this->width = width;
	this->height = height;
	glViewport(0,0,width,height);
	SetView();
}

void App::Mouse(int button,int state,int x,int y) {}

void App::MouseDrag(int x,int y) {}

void App::RenderText(float x,float y,const char *text,void *font)
{
	glDisable(GL_DEPTH_TEST);

	//temporarily set view to orthographic
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0,(double)width,0.0,(double)height,-1.0,1.0);

	//move to modelview mode
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//ensure we have a font
	if(font == 0)
	{
		font = GLUT_BITMAP_HELVETICA_18;
	}

	//loop through characters and display them
	size_t len = strlen(text);

	glRasterPos2f(x,y);
	for(const char *letter=text; letter<text+len; letter++)
	{
		//if we meet a newline, then move down by the line-height
		if(*letter == '\n')
		{
			y -= 12.0f;
			glRasterPos2f(x,y);
		}
		glutBitmapCharacter(font,*letter);
	}

	//pop the matrices to return to how we were before
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
}

void App::DrawGrid()
{
	//draw grid
	float width = 5.0f;
	float space = 0.5f;
	glColor3f(0.35f,0.35f,0.35f);
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	for(int i=-10; i<=10; i++)
	{
		if(i == 0)
		{
			glLineWidth(2.0f);
			glColor3f(0.0f,0.0f,0.0f);
		}
		glVertex3f(-width,0.0f,i*space);
		glVertex3f(width,0.0f,i*space);
		glVertex3f(i*space,0.0f,-width);
		glVertex3f(i*space,0.0f,width);
		if(i == 0)
		{
			glLineWidth(1.0f);
			glColor3f(0.35f,0.35f,0.35f);
		}
	}
	glEnd();
}

void App::DrawFPS()
{
	std::string fpsStr = "FPS: ";

	timeStep += timer.getFrameTime();
	if(timeStep >= fpsUpdate)
	{
		timeStep = 0.0f;
		cachedFPS = timer.getFPS();
	}

	std::stringstream sstream;
	sstream << (int)cachedFPS;
	fpsStr += sstream.str();

	glColor3f(1,1,1);
	RenderText(10.0f,(float)height-20.0f,fpsStr.c_str());
}

}
