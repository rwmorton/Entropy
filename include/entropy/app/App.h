#ifndef __Application_h__
#define __Application_h__

//local dependencies
#include <entropy\sys\timer.h>

namespace entropy
{

//Base class for implementing applications.
class App
{
	public:
		//constructor
		App();
		//destructor
		virtual ~App();
		//methods
		const int GetWidth() const;
		void SetWidth(int width);
		const int GetHeight() const;
		void SetHeight(int height);
		virtual const char *GetTitle();
		virtual void InitializeGraphics();
		virtual void SetView();
		virtual void Deinitialize();
		virtual void Display();
		virtual void Update();
		virtual void Key(unsigned char key);
		virtual void Resize(int width,int height);
		virtual void Mouse(int button,int state,int x,int y);
		virtual void MouseDrag(int x,int y);
		void RenderText(float x,float y,const char *text,void *font=0);
	private:
		//
	protected:
		//methods
		virtual void DrawGrid();
		virtual void DrawFPS();
		//data
		int width,height;
		Timer timer;
		float cachedFPS,timeStep,fpsUpdate;
};

}

#endif
