#ifndef __timer_h__
#define __timer_h__

namespace entropy
{

class Timer
{
public:
	//constructor
	Timer();
	//methods
	void update();
	unsigned int getTicks();
	float getFrameTime();
	float getTotalTime();
	float getFPS();
private:
	//prevent copies
	Timer(const Timer &);
	Timer &operator=(const Timer &);
	//variables
	float totalTime,frameTime;
protected:
	//
};

}

#endif
