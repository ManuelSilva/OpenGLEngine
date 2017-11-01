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

Engine::EngineCore* Engine::EngineCore::_EngineCore_instance;	
#define SHADER_PATH ".\\..\\..\\dependencies\\shaders\\"

typedef struct {
	EngineMath::vec4 XYZW;
}Vertex;

GLint UboId, UniformId;
const GLuint UBO_BP = 0;

Engine::Camera _mainCamera(MatrixFactory::identity());


void render();
void update(float delta);

void keyboardInput(unsigned char key, int x, int y);
void mouseInput(int x, int y);

void createScene();
void geometryFunction(Engine::GameObject obj);
void geometryDraw(Engine::GameObject obj);
Engine::Shader shaderSetUp();


#endif // !__MAIN_H__
