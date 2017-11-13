#ifndef __SCENE_H__
#define __SCENE_H__
#pragma once
#include "GameObject.h"
#include "Camera.h"
#include <map>
#include <vector>
#include <string>

namespace Engine {

	class GameObject;
	class Camera;

	class Scene {
	private:
		unsigned int uniqueId;

	public:
		std::map<unsigned int, GameObject> _gameObjects;
		EngineMath::mat4 calculatedMatrixStack;
	public:
		Scene();
		~Scene();

		void push(GameObject obj);
		void draw(Camera camera);
	};


	EngineMath::mat4 getObjectMatrix(Scene scene, GameObject obj, EngineMath::mat4 mat);
}

#endif