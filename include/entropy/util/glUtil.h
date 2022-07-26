#ifndef __glUtil_h__
#define __glUtil_h__

//local dependencies
#include <entropy\cfg.h>
#include <entropy\math\r2\point2.h>
#include <entropy\math\r3\point3.h>
#include <entropy\math\r2\vector2.h>
#include <entropy\math\r3\vector3.h>
#include <entropy\math\r2\transform2.h>
#include <entropy\math\r3\transform3.h>
#include <entropy\math\r2\ray2.h>
#include <entropy\math\r3\ray3.h>
#include <entropy\color\color.h>

namespace entropy
{

class GlUtil
{
public:
	//static methods
	//draw points
	static void drawPoint(const Point2 &p,float size,const Color &c=Color::WHITE);
	static void drawPoint(const Point3 &p,float size,const Color &c=Color::WHITE);
	//draw lines
	static void drawLine(const Point2 &p1,const Point2 &p2,float lineWidth=1.0f,const Color &c=Color::WHITE);
	static void drawLine(const Point3 &p1,const Point3 &p2,float lineWidth=1.0f,const Color &c=Color::WHITE);
	//draw 2d shapes
	static void drawLineLoop(const Transform2 &t,const Point2 *p,int size,float lineWidth=1.0f,const Color &c=Color::WHITE);
	static void drawCircle(const Point2 &p,float radius,int segs,float lineWidth=1.0f,const Color &c=Color::WHITE);
	static void drawBox(const Point2 &min,const Point2 &max,float lineWidth=1.0f,const Color &c=Color::WHITE);
	//draw vectors
	static void drawVector(const Vector2 &v,const Point2 &place,float lineWidth=1.0f,const Color &c=Color::RED);
	static void drawVector(const Vector3 &v,const Point3 &place,float lineWidth=1.0f,const Color &c=Color::RED);
	//draw rays
	static void drawRay(const Ray2 &r,float lineExtend,const Color &vc=Color::RED,const Color &lc=Color::BLUE);
	static void drawRay(const Ray3 &r,float lineExtend,const Color &vc=Color::RED,const Color &lc=Color::BLUE);
private:
	//
protected:
	//
};

}

#endif
