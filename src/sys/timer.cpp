//local dependencies
#include <entropy\sys\timer.h>
#include <entropy\cfg.h>

namespace entropy
{

Timer::Timer() : totalTime(0.0f),frameTime(0.0f) {}

//update timer
void Timer::update()
{
	float newTime = ((float)getTicks()) * 0.001f; //convert to seconds
	frameTime = newTime - totalTime;
	totalTime = newTime;
}

//get current system time in milliseconds
unsigned int Timer::getTicks()
{
	return glutGet(GLUT_ELAPSED_TIME);
}

//get frame time
float Timer::getFrameTime()
{
	return frameTime;
}

//get total time
float Timer::getTotalTime()
{
	return totalTime;
}

//get FPS
float Timer::getFPS()
{
	return 1.0f / frameTime;
}

}
