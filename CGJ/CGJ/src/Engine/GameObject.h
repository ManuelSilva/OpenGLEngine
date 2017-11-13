#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#pragma once
#include <vector>
#include "../Math/Math.h"
#include "Shader.h"
#include "Mesh.h"

namespace Engine {


	class GameObject {
	public:
		void(*drawfunc)(Engine::GameObject obj);
		void(*geoFunc)(Engine::GameObject obj);

	public:
		EngineMath::mat4 modelMatrix;
		unsigned int uniqueId;
		unsigned int parentId;
		std::vector<unsigned int> children;
		std::string tag;
		Shader _prog;
		Mesh::Mesh geo;
	public:
		GameObject();
		GameObject(Shader prog, void(*drawfunc)(Engine::GameObject obj1), void(*geofunc)(Engine::GameObject obj2));
		~GameObject();
		void setParent(GameObject obj);
		void draw(Engine::GameObject obj);
		void setDrawFunction(void(*func)(Engine::GameObject obj));
		void setGeometryFunction(void(*func)(Engine::GameObject obj));
		void useGeoFunc(GameObject obj);
		EngineMath::mat4 getModelMatrix();
		
	};
		GameObject duplicateGameObject(GameObject obj);
}

#endif
