#ifndef __demos_h__
#define __demos_h__

#include <iostream>
#include <conio.h>
#include <list>
#include <sstream>
using namespace std;

#include <entropy\entropy.h>
using namespace entropy;

//
//-----------------------------------------------------------------
//
class NewAi1 : public App
{
public:
	NewAi1();
	~NewAi1();
	void Display();
	void Update();
	void Key(unsigned char key);
private:
	//variables
	Timer timer;
	Vehicle *agent,targetVehicle;
	SteeringBehaviours *steering;
	Point2 target;
	int NUM_BOIDS;
	float X_EXTENT,Y_EXTENT;
	std::vector<Entity> obstacles;
	int NUM_OBS;
	Ray2 r;
	Circle c;
	bool worldSpace;
};
//-----------------------------------------------------------------
//

#endif
