#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#pragma once
#include <vector>
#include "../Math/Math.h"
#include "Shader.h"
#include "Mesh.h"

namespace Engine {

	struct AnimationInfo {
		EngineMath::vec3 initial_position = EngineMath::vec3(0,0,0);
		EngineMath::Quaternion initial_rotation = EngineMath::Quaternion();
		EngineMath::vec3 initial_scale = EngineMath::vec3(0,0,0);

		EngineMath::vec3 target_position = EngineMath::vec3(0, 0, 0);
		EngineMath::Quaternion target_rotation = EngineMath::Quaternion();
		EngineMath::vec3 target_scale = EngineMath::vec3(0, 0, 0);

		EngineMath::vec3 prevLerp = EngineMath::vec3(0, 0, 0);

		float rate = 0;
	};


	class GameObject {
	public:
		void(*drawfunc)(Engine::GameObject obj);
		void(*geoFunc)(Engine::GameObject obj);

	public:
		EngineMath::mat4 modelMatrix;
		EngineMath::mat4 tranformations;
		unsigned int uniqueId;
		unsigned int parentId;
		std::vector<unsigned int> children;
		std::string tag;
		Shader _prog;
		Mesh::Mesh geo;
		AnimationInfo animationInfo;
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
		void push(EngineMath::mat4 transformation, bool apply2Children);
	};
		GameObject duplicateGameObject(GameObject obj);
}

#endif
