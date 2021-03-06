#ifndef __MAIN_H__
#define __MAIN_H__

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "Math\Math.h"
#include "Engine\Engine.h"

#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <map>
#include <algorithm>


Engine::EngineCore* Engine::EngineCore::_EngineCore_instance;	
#define SHADER_PATH ".\\..\\..\\dependencies\\shaders\\"
#define OBJ_PATH ".\\..\\..\\dependencies\\assets\\models\\blender_2.79\\"

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2


Engine::Camera _mainCamera(MatrixFactory::identity());

unsigned int backgroundID = -1;

void render();
void update(float delta);

void mouseInput(int x, int y);

void createScene();
void geometryFunction(Engine::GameObject obj);
void geometryDraw(Engine::GameObject obj);
Engine::Shader shaderSetUp();

Engine::Scene animate();
void switchAnimation();

#endif // !__MAIN_H__
