//local dependencies
#include <entropy\util\glUtil.h>
#include <entropy\math\math.h>

namespace entropy
{

void GlUtil::drawPoint(const Point2 &p,float size,const Color &c)
{
	glPointSize(size);
	glColor3f(c.r,c.g,c.b);
	glBegin(GL_POINTS);
	glVertex2f(p.x,p.y);
	glEnd();
}

void GlUtil::drawPoint(const Point3 &p,float size,const Color &c)
{
	glPointSize(size);
	glColor3f(c.r,c.g,c.b);
	glBegin(GL_POINTS);
	glVertex3f(p.x,p.y,p.z);
	glEnd();
}

void GlUtil::drawLine(const Point2 &p1,const Point2 &p2,float lineWidth,const Color &c)
{
	glColor3f(c.r,c.g,c.b);
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	glVertex2f(p1.x,p1.y);
	glVertex2f(p2.x,p2.y);
	glEnd();
}

void GlUtil::drawLine(const Point3 &p1,const Point3 &p2,float lineWidth,const Color &c)
{
	glColor3f(c.r,c.g,c.b);
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	glVertex3f(p1.x,p1.y,p1.z);
	glVertex3f(p2.x,p2.y,p2.z);
	glEnd();
}

void GlUtil::drawLineLoop(const Transform2 &t,const Point2 *p,int size,float lineWidth,const Color &c)
{
	glLineWidth(lineWidth);
	glColor3f(c.r,c.g,c.b);
	glBegin(GL_LINE_LOOP);
	Point2 pt;
	for(int i=0; i<size; i++)
	{
		pt = t(*p);
		glVertex2f(pt.x,pt.y);
		p++;
	}
	glEnd();
}

void GlUtil::drawCircle(const Point2 &p,float radius,int segs,float lineWidth,const Color &c)
{
	glColor3f(c.r,c.g,c.b);
	float incr = Math::TWO_PI / segs;
	glLineWidth(lineWidth);
	glPushMatrix();
	glTranslatef(p.x,p.y,0.0f);
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<segs; i++)
	{
		glVertex2f
		(
			Math::cos(i*incr) * radius,
			Math::sin(i*incr) * radius
		);
	}
	glEnd();
	glPopMatrix();
}

void GlUtil::drawBox(const Point2 &min,const Point2 &max,float lineWidth,const Color &c)
{
	glColor3f(c.r,c.g,c.b);
	glLineWidth(lineWidth);
	//draw in a counterclockwise order
	Point2 center
	(
		(min.x + max.x) / 2.0f,
		(min.y + max.y) / 2.0f
	);
	Vector2 maxVec = max - center;
	maxVec = maxVec.perpendicular();
	Vector2 minVec = min - center;
	minVec = minVec.perpendicular();

	glBegin(GL_LINE_LOOP);
	glVertex2f(max.x,max.y);
	glVertex2f(center.x + maxVec.x,center.y + maxVec.y);
	glVertex2f(min.x,min.y);
	glVertex2f(center.x + minVec.x,center.y + minVec.y);
	glEnd();
}

void GlUtil::drawVector(const Vector2 &v,const Point2 &place,float lineWidth,const Color &c)
{
	glLineWidth(lineWidth);
	GlUtil::drawPoint(place,5,c);
	GlUtil::drawLine(place,place + v,lineWidth,c);
	GlUtil::drawPoint(place + v,3,c);
}

void GlUtil::drawVector(const Vector3 &v,const Point3 &place,float lineWidth,const Color &c)
{
	glLineWidth(lineWidth);
	GlUtil::drawPoint(place,5,c);
	GlUtil::drawLine(place,place + v,lineWidth,c);
	GlUtil::drawPoint(place + v,3,c);
}

void GlUtil::drawRay(const Ray2 &r,float lineExtend,const Color &vc,const Color &lc)
{
	GlUtil::drawVector(r.getDirection(),r.getOrigin(),2.0f,vc);
	GlUtil::drawLine(r.getOrigin(),r(lineExtend),1.0f,lc);
}

void GlUtil::drawRay(const Ray3 &r,float lineExtend,const Color &vc,const Color &lc)
{
	GlUtil::drawVector(r.getDirection(),r.getOrigin(),2.0f,vc);
	GlUtil::drawLine(r.getOrigin(),r(lineExtend),1.0f,lc);
}

}
