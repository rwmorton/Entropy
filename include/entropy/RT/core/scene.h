#ifndef __scene_h__
#define __scene_h__

//local dependencies
#include <entropy\cfg.h>
#include <entropy\RT\core\shape.h>

namespace entropy
{

class Scene
{
public:
	//destructor
	~Scene();
	//methods
	bool loadScene(const String &file);
	bool render() const;
private:
	//variables
	Shape *shapes;
protected:
	//
};

}

#endif
