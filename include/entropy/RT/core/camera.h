#ifndef __camera_h__
#define __camera_h__

//local dependencies
#include <entropy\math\r3\transform3.h>

namespace entropy
{

class Camera
{
public:
	//constructor
	Camera
	(
		const Transform3 &c2w,
		float n,float f,
		float so,float sc
	) : cameraToWorld(c2w),worldToCamera(c2w.inverse()),nearClip(n),farClip(far),shutterOpen(so),shutterClose(sc) {}
	//destructor
	virtual ~Camera() {}
	//methods
	float getNearClip() { return nearClip; }
	void setNearClip(float n) { nearClip = n; }
	float getFarClip() { return farClip; }
	void setFarClip(float f) { farClip = f; }
	float getShutterOpen() { return shutterOpen; }
	void setShutterOpen(float so) { shutterOpen = so; }
	float getShutterClose() { return shutterClose; }
	void setShutterClose(float sc) { shutterClose = sc; }
	virtual void GENERATE_RAY() = 0; //TEMP
private:
	//
protected:
	//variables
	Transform3 cameraToWorld;
	Transform3 worldToCamera;
	float nearClip;
	float farClip;
	float shutterOpen;
	float shutterClose;
};

}

#endif
