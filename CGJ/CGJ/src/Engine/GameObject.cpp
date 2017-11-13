#include "GameObject.h"


Engine::GameObject::GameObject()
{
	parentId = -1;
	uniqueId = uniqueId = Numbers::giveId();
}

Engine::GameObject::GameObject(Shader prog, void(*drawf)(Engine::GameObject obj1), void(*geof)(Engine::GameObject obj2))
{
	parentId = -1;
	uniqueId = uniqueId = Numbers::giveId();
	modelMatrix = MatrixFactory::identity();
	drawfunc = drawf;
	geoFunc = geof;
	_prog = prog;
}

Engine::GameObject::~GameObject()
{
}

void Engine::GameObject::setParent(GameObject obj)
{
	parentId = obj.uniqueId;
	obj.children.push_back(uniqueId);
}

void Engine::GameObject::draw(Engine::GameObject obj)
{
	if (drawfunc) {
		drawfunc(obj);
	}
	else {
		std::cout << "Object with id - " <<  uniqueId << " has no drawing function" <<std::endl;
	}
}

void Engine::GameObject::setDrawFunction(void(*func)(Engine::GameObject obj))
{
	drawfunc = func;

}

void Engine::GameObject::setGeometryFunction(void(*func)(Engine::GameObject obj))
{
	geoFunc = func;
}

void Engine::GameObject::useGeoFunc(GameObject obj)
{
	if (geoFunc) {
		geoFunc(obj);
	}
}

EngineMath::mat4 Engine::GameObject::getModelMatrix()
{
	return modelMatrix;
}

Engine::GameObject Engine::duplicateGameObject(GameObject obj)
{
	Engine::GameObject aux = Engine::GameObject(obj._prog,obj.drawfunc, obj.geoFunc);
	aux.geo = obj.geo;
	aux.modelMatrix = obj.modelMatrix;
	return aux;
}
