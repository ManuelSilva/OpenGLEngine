#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#pragma once
#include <vector>
#include "../Math/Math.h"
#include "Shader.h"

namespace Engine {


	struct Geometry {
		EngineMath::glVec4 color = EngineMath::glVec4(EngineMath::vec4(1.0f,1.0f,1.0f,1.0f));
		std::vector<EngineMath::vec4> Vertices;
		std::vector<EngineMath::vec4> Colors;
		std::vector<GLubyte> Indexes;
		GLuint VaoId;
		GLuint VboId[2];
	};


	class GameObject {
	public:
		void(*drawfunc)(Engine::GameObject obj);
		void(*geoFunc)(Engine::GameObject obj);

	public:
		unsigned int uniqueId;
		unsigned int parentId;
		EngineMath::mat4 modalMatrix, objectMatrix;
		std::vector<unsigned int> children;
		std::string tag;
		Shader _prog;
		Geometry geo;
	public:
		GameObject();
		GameObject(Shader prog, void(*drawfunc)(Engine::GameObject obj1), void(*geofunc)(Engine::GameObject obj2));
		~GameObject();
		void setParent(GameObject obj);
		void draw(Engine::GameObject obj);
		void setDrawFunction(void(*func)(Engine::GameObject obj));
		void setGeometryFunction(void(*func)(Engine::GameObject obj));
		void useGeoFunc(GameObject obj);
		
	};
		GameObject duplicateGameObject(GameObject obj);
}

#endif
