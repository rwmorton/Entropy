//local dependencies
#include <entropy\RT\core\scene.h>

namespace entropy
{

Scene::~Scene()
{
	if(shapes)
	{
		delete[] shapes;
	}
}

bool Scene::loadScene(const String &file)
{
	return false; //TODO
}

bool Scene::render() const
{
	return false; //TODO
}

}
