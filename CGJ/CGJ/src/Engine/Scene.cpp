#include "Scene.h"


Engine::Scene::Scene()
{
	uniqueId = Numbers::giveId();
}

Engine::Scene::~Scene()
{
}

void Engine::Scene::push(GameObject obj)
{
	_gameObjects[obj.uniqueId] = obj;
}

void Engine::Scene::draw(Camera camera)
{

	for(std::map<unsigned int, GameObject>::iterator it = _gameObjects.begin(); it!= _gameObjects.end(); ++it)
	{	
		it->second.modalMatrix = camera.getProjectionMatrix() * camera.getViewMatrix() * it->second.objectMatrix;

		it->second.draw(it->second);
	}
}


