#ifndef __GLUTWrapper_h__
#define __GLUTWrapper_h__

//local dependencies
#include <entropy\app\App.h>

namespace entropy
{
//Wrapper class for GLUT. Provides callback functions
//for GLUT that are linked the the application instance.
//This class implements a function to setup GLUT and
//run the application.
//
//The standard way to use GLUTWrapper is:
//
//int main(int argc,char **argv)
//{
//	GLUTWrapper::SetApplication(new MyTestApp);
//	GLUTWrapper::Run(argc,argv);
//	return 0;
//}
//
//Where GLUTWrapper will take care of the heap-allocated
//application instance that was passed to SetApplication().
class GLUTWrapper
{
	public:
		//destructor
		~GLUTWrapper();
		//methods
		static void SetApplication(App *app);
		static App *GetApplication();
		static void Run(int argc,char **argv);
	private:
		//methods
		static void __cdecl CreateWindow(const char *title=0);
		static void __cdecl Update();
		static void __cdecl Display();
		static void __cdecl Mouse(int button,int state,int x,int y);
		static void __cdecl MouseDrag(int x,int y);
		static void __cdecl Resize(int width,int height);
		static void __cdecl Keyboard(unsigned char key,int x,int y);
		//data
		static App *app;
		//prevent instances of this
		//class being instantiated.
		GLUTWrapper();
		GLUTWrapper(const GLUTWrapper &right);
		GLUTWrapper &operator=(const GLUTWrapper &right);
	protected:
		//
};

}

#endif
