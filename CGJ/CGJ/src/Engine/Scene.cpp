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
		it->second.draw(it->second);
	}
}

EngineMath::mat4 Engine::getObjectMatrix(Scene scene, GameObject obj, EngineMath::mat4 mat)
{
	mat = mat * obj.modelMatrix;
	if (obj.parentId != -1) {
		mat = getObjectMatrix(scene, scene._gameObjects[obj.parentId], mat);
	}
	return mat;
}
