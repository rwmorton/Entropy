#include <demos.h>

NewAi1::NewAi1()
{
	NUM_BOIDS = 5;
	NUM_OBS = 3;

	agent = new Vehicle[NUM_BOIDS];
	steering = new SteeringBehaviours[NUM_BOIDS];

	for(int i=0; i<NUM_BOIDS; i++)
	{
		agent[i].steering = &steering[i];

		agent[i].position = Point2(Math::randomBinomial() * 5,Math::randomBinomial() * 5);
		agent[i].velocity = Vector2::ZERO;
		agent[i].mass = 0.1f;
		agent[i].maxSpeed = Math::max(5.0f,Math::random(12.0f)); //5.0f;

		//agent[i].faceTarget(Point2(Math::randomBinomial(),Math::randomBinomial()));

		steering[i].vehicle = &agent[i];
		steering[i].target = &target;
		steering[i].deceleration = 0.5f;
		steering[i].evadeDistance = 3.0f;
		steering[i].seekWeight = 0.5f;
		steering[i].evadeWeight = 0.5f;
		steering[i].wanderWeight = 1.0f;
		steering[i].wanderRadius = Math::max(0.25f,Math::random(1.0f)); //0.75f;
		steering[i].wanderDistance = Math::max(2.0f,Math::random(5.0f)); //5.0f;
		steering[i].wanderJitter = 0.5f;

		obstacles.push_back(agent[i]);
	}

	//create our obstacles
	obstacles.push_back(Entity(Circle(Point2(-7,5),2.0f)));
	obstacles.push_back(Entity(Circle(Point2(-7,-2),3.0f)));
	obstacles.push_back(Entity(Circle(Point2(8,-6),2.0f)));

	X_EXTENT = 12.0f;
	Y_EXTENT = 9.0f;

	c = Circle(Point2(2,3),2.0f);
	r = Ray2(Point2(-1,5),Vector2(1,-1));
	worldSpace = true;
}

NewAi1::~NewAi1()
{
	delete[] agent;
	delete[] steering;
}

void NewAi1::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0,15,0.001f,0,0,0,0,1,0);

	glMatrixMode(GL_MODELVIEW);
	glRotatef(-90.0f,1.0f,0.0f,0.0f); //rotate to align xy plane

	/*
	//for each agent
	for(int j=0; j<NUM_BOIDS; j++)
	{
		agent[j].render();

		//render obstacles
		for(int i=0; i<obstacles.size(); i++)
		{
			GlUtil::drawCircle(obstacles[i].bound.getCenter(),obstacles[i].bound.getRadius(),32,1.0f,obstacles[i].color);
		}
	}*/

	Intersection2 isct;
	bool gotHit = c.intersect(r,isct);
	Transform2 localToWorld = Transform2::translate(Vector2(c.getCenter().x,c.getCenter().y));
	Transform2 worldToLocal = localToWorld.inverse();
	if(worldSpace)
	{
		if(gotHit)
		{
			GlUtil::drawPoint(isct.p,5.0f,Color::RED);
		}
		GlUtil::drawCircle(c.getCenter()/*localToWorld(Point2::ZERO)*/,c.getRadius(),32,1.0f);
		GlUtil::drawRay(r,10.0f);
	}
	else
	{
		if(gotHit)
		{
			GlUtil::drawPoint(worldToLocal(isct.p),5.0f,Color::RED);
			GlUtil::drawPoint(isct.p,5.0f,Color::WHITE);
		}
		GlUtil::drawCircle(c.getCenter()/*localToWorld(Point2::ZERO)*/,c.getRadius(),32,1.0f,Color::RED);
		GlUtil::drawCircle(Point2::ZERO/*localToWorld(Point2::ZERO)*/,c.getRadius(),32,1.0f);
		GlUtil::drawRay(worldToLocal(r),10.0f);
	}

	//
	Vehicle v;
	v.position = Point2(1,2);
	v.front = Vector2(1,1);

	v.localToWorld = (Transform2::rotate(Math::aTan2(v.front.y,v.front.x)))(Transform2::translate(Vector2(v.position.x,v.position.y)));
	v.worldToLocal = v.localToWorld.inverse();

	if(worldSpace)
	{
		v.render();
	}
	else
	{
		//Algo::swap<Transform2>(v.localToWorld,v.worldToLocal);

		v.localToWorld = v.worldToLocal.inverse();

		v.render();

		//Algo::swap<Transform2>(v.localToWorld,v.worldToLocal);
	}

	glPushMatrix();
	glRotatef(90,1,0,0);
	App::DrawGrid();
	glPopMatrix();

	glPopMatrix(); //pop modelview matrix

	App::DrawFPS();
}

void NewAi1::Update()
{
	float step = timer.getFrameTime();

	/*
	for(int i=0; i<NUM_BOIDS; i++)
	{
		//run behaviours and update agent
		steering[i].wander();
		steering[i].obstacleAvoidance(obstacles);
		agent[i].update(step);

		//simulate toroidal world
		if(agent[i].position.x > X_EXTENT)
		{
			agent[i].position.x = -X_EXTENT;
		}
		if(agent[i].position.x < -X_EXTENT)
		{
			agent[i].position.x = X_EXTENT;
		}
		if(agent[i].position.y > Y_EXTENT)
		{
			agent[i].position.y = -Y_EXTENT;
		}
		if(agent[i].position.y < -Y_EXTENT)
		{
			agent[i].position.y = Y_EXTENT;
		}
	}
	*/

	timer.update();
	App::Update();
}

void NewAi1::Key(unsigned char key)
{
	switch(key)
	{
		case 's':
			worldSpace = !worldSpace;
			break;
		case 27:
			exit(0);
	}
}
