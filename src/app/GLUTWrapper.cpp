//std dependencies
#include <cstdlib> //must be included before GLUT

//GLUT dependencies
#include <gl/glut.h>

//local dependencies
#include <entropy\app\GLUTWrapper.h>

namespace entropy
{

//static member declaritions
App *GLUTWrapper::app = 0;

GLUTWrapper::~GLUTWrapper()
{
	delete GLUTWrapper::app;
}

void GLUTWrapper::SetApplication(App *app)
{
	if(GLUTWrapper::app)
	{
		delete GLUTWrapper::app;
	}
	GLUTWrapper::app = app;
}

App *GLUTWrapper::GetApplication()
{
	return GLUTWrapper::app;
}

void GLUTWrapper::Run(int argc,char **argv)
{
	//first check if we have a valid application instance
	if(!app)
	{
		//error!
		abort();
	}

	//initialize GLUT
	glutInit(&argc,argv);

	//create window
	GLUTWrapper::CreateWindow(app->GetTitle());

	//set up the appropriate handler functions
	glutReshapeFunc(&GLUTWrapper::Resize);
	glutKeyboardFunc(&GLUTWrapper::Keyboard);
	glutDisplayFunc(&GLUTWrapper::Display);
	glutIdleFunc(&GLUTWrapper::Update);
	glutMouseFunc(&GLUTWrapper::Mouse);
	glutMotionFunc(&GLUTWrapper::MouseDrag);

	//run the application
	app->InitializeGraphics();
	glutMainLoop();

	//clean up
	app->Deinitialize();
}

void GLUTWrapper::CreateWindow(const char *title)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(app->GetWidth(),app->GetHeight());
	glutInitWindowPosition(0,0);
	glutCreateWindow(title);
}

void GLUTWrapper::Update()
{
	//update the applications clock
	//
	//update the application
	app->Update();
}

void GLUTWrapper::Display()
{
	app->Display();
	//update the OpenGL state
	glFlush();
	glutSwapBuffers();
}

void GLUTWrapper::Mouse(int button,int state,int x,int y)
{
	app->Mouse(button,state,x,y);
}

void GLUTWrapper::MouseDrag(int x,int y)
{
	app->MouseDrag(x,y);
}

void GLUTWrapper::Resize(int width,int height)
{
	app->Resize(width,height);
}

void GLUTWrapper::Keyboard(unsigned char key,int x,int y)
{
	app->Key(key);
}

}
