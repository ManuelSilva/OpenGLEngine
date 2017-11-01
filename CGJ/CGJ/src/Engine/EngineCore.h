#ifndef __ENGINECORE_H__
#define __ENGINECORE_H__
#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "Scene.h"
#include <iostream>
#include <sstream>
#include <string>


#define GETCORE Engine::EngineCore *core = Engine::EngineCore::getEngineCore();
#define WAIT int wait = 0; std::cin >> wait;
#define FPS 60

static int _WindowHandle;


namespace Engine{

	class Scene;

	void engine_timer(int value);
	void engine_reshape(int w, int h);
	void engine_display();
	void engine_idle();
	void engine_cleanup();
	void engine_fpsLimit(int value);
	void engine_PostRedisplay();
	void engine_keyboardInput(unsigned char key, int x, int y);
	void  engine_mouseInput(int x, int y);

	void engine_CreateScene();


	struct Engine_GLUT_Properties{
		int Engine_OpenGL_Version = 3;
		int Engine_OpenGL_SubVersion = 3;
		int Engine_glutInitContextProfile = GLUT_CORE_PROFILE;
		int Engine_glutInitContextFlags = GLUT_FORWARD_COMPATIBLE;
		int Engine_glutSetOption_flag = GLUT_ACTION_ON_WINDOW_CLOSE;
		int Engine_glutSetOption_value = GLUT_ACTION_GLUTMAINLOOP_RETURNS;
		int Engine_windowSize_x = 500;
		int Engine_windowSize_y = 500;
		int Engine_glutInitDisplayMode = GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA;
		char* Engine_windowName = "default_name";
	};

	struct Engine_OpenGL_Info {
		const GLubyte *renderer;
		const GLubyte *vendor;
		const GLubyte *version;
		const GLubyte *glslVersion;
	};


	class EngineCore {
	private:
		static EngineCore * _EngineCore_instance;
		
		bool _closingEngine = false;
		//Callback_Functions
		void(*renderFunc)() = engine_display;
		void(*clearFunc)() = engine_cleanup;
		void(*sceneCreateFunc)() = engine_CreateScene;
		void(*keyboardFunc)(unsigned char key, int x, int y) = engine_keyboardInput;
		void(*mouseFunc)(int x, int y) = engine_mouseInput;
	public:
		Engine_GLUT_Properties _Active_GLUT_Properties;
		Engine_OpenGL_Info _OpenGLInfo;
		unsigned int _FrameCount = 0;
		Scene _mainScene;

	private:
		EngineCore();
		~EngineCore();
		void geoCreateFunc();
	public:
		static EngineCore * getEngineCore();
		void startEngine(int argc, char* argv[]);
		void shutdown();
		//---------------------------------
		//---------------------------------
		bool isOpenGLError();
		void checkOpenGLError(std::string error);
		void checkOpenGLInfo();
		bool isShutdown();

		//setUps
		void setupGLUT(int argc,char* argv[]);
		void setupGLEW();
		void setupOpenGL();
		void setupCallbacks();

		void setUpSceneCreateFunc(void(*createScene)());
		void setUpRenderFunc(void(*display)());
		void setUpClearFunc(void(*clear)());
		void setUpKeyboardFunc(void(*keyboardFunc)(unsigned char key, int x, int y));
		void setUpMouseFunc(void(*func)(int x, int y));


		float getDeltaTime();

	
		};
}


#endif
