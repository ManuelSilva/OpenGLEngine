#include "EngineCore.h"

Engine::EngineCore::EngineCore(){}

Engine::EngineCore::~EngineCore(){}

Engine::EngineCore * Engine::EngineCore::getEngineCore()
{
	if (!_EngineCore_instance) {
		_EngineCore_instance = new EngineCore();
	}
	return _EngineCore_instance;
}

//-----------------------------------------------------------------------------------
void Engine::EngineCore::geoCreateFunc()
{

	for (std::map<unsigned int, GameObject>::iterator it = _mainScene._gameObjects.begin(); it != _mainScene._gameObjects.end(); ++it)
	{
		it->second.useGeoFunc(it->second);
	}
}

//----------------------------------------------------------------------------------

void Engine::EngineCore::startEngine(int argc, char* argv[]){
	_closingEngine = false;
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	sceneCreateFunc();
	geoCreateFunc();
	setupCallbacks();
	glutMainLoop();
}

void Engine::EngineCore::shutdown()
{
	_closingEngine = true;
}

bool Engine::EngineCore::isOpenGLError()
{
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

void Engine::EngineCore::checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		WAIT
	}
}

void Engine::EngineCore::checkOpenGLInfo()
{
	_OpenGLInfo.renderer = glGetString(GL_RENDERER);
	_OpenGLInfo.vendor = glGetString(GL_VENDOR);
	_OpenGLInfo.version = glGetString(GL_VERSION);
	_OpenGLInfo.glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << _OpenGLInfo.renderer << " (" << _OpenGLInfo.vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << _OpenGLInfo.version << std::endl;
	std::cerr << "GLSL version " << _OpenGLInfo.glslVersion << std::endl;
}

bool Engine::EngineCore::isShutdown()
{
	return _closingEngine;
}

//-----------------------------------------------------------------------------------

void Engine::EngineCore::setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(_Active_GLUT_Properties.Engine_OpenGL_Version, _Active_GLUT_Properties.Engine_OpenGL_SubVersion);
	glutInitContextProfile(_Active_GLUT_Properties.Engine_glutInitContextProfile);
	glutInitContextFlags(_Active_GLUT_Properties.Engine_glutInitContextFlags);
	glutSetOption(_Active_GLUT_Properties.Engine_glutSetOption_flag, _Active_GLUT_Properties.Engine_glutSetOption_value);
	glutInitWindowSize(_Active_GLUT_Properties.Engine_windowSize_x, _Active_GLUT_Properties.Engine_windowSize_y);
	glutInitDisplayMode(_Active_GLUT_Properties.Engine_glutInitDisplayMode);
	_WindowHandle = glutCreateWindow(_Active_GLUT_Properties.Engine_windowName);
	if (_WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		WAIT
		exit(EXIT_FAILURE);
	}
}

void Engine::EngineCore::setupGLEW()
{
	glewExperimental = GL_TRUE;

	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		WAIT
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
}

void Engine::EngineCore::setupOpenGL()
{
	checkOpenGLInfo();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void Engine::EngineCore::setupCallbacks()
{
	glutCloseFunc(clearFunc);
	glutDisplayFunc(renderFunc);
	glutKeyboardFunc(keyboardFunc);
	glutPassiveMotionFunc(mouseFunc);
	glutIdleFunc(engine_idle);
	glutReshapeFunc(engine_reshape);
	glutTimerFunc(0, engine_timer, 0);
	#ifdef FPS
	glutTimerFunc(0, engine_fpsLimit, 0);	
	#endif
}

void Engine::EngineCore::setUpSceneCreateFunc(void(*createScene)())
{
	sceneCreateFunc = createScene;
}

void Engine::EngineCore::setUpRenderFunc(void(*display)())
{
	renderFunc = display;
}

void Engine::EngineCore::setUpClearFunc(void(*clear)())
{
	clearFunc = clear;
}

void Engine::EngineCore::setUpKeyboardFunc(void(*func)(unsigned char key, int x, int y))
{
	keyboardFunc = func;
}

void Engine::EngineCore::setUpMouseFunc(void(*func)(int x, int y))
{
	mouseFunc = func;
}

float Engine::EngineCore::getDeltaTime()
{
	static float prev_time = 0;
	float curr_time = glutGet(GLUT_ELAPSED_TIME)*1.0f;
	float delta_time = (curr_time - prev_time)/100.0f;
	prev_time = curr_time;
	return delta_time;
}



//---------------------------------------------------------------------------------

void Engine::engine_timer(int value)
{
	GETCORE
	std::ostringstream oss;
	oss << core->_Active_GLUT_Properties.Engine_windowName 
		<< ": " << core->_FrameCount << " FPS @ (" << 
		core->_Active_GLUT_Properties.Engine_windowSize_x << "x" 
		<< core->_Active_GLUT_Properties.Engine_windowSize_y << ")";
	std::string s = oss.str();
	glutSetWindow(_WindowHandle);
	glutSetWindowTitle(s.c_str());
	core->_FrameCount = 0;
	glutTimerFunc(1000, engine_timer, 0);
}

void Engine::engine_reshape(int w, int h)
{
	GETCORE
	core->_Active_GLUT_Properties.Engine_windowSize_x = w;
	core->_Active_GLUT_Properties.Engine_windowSize_y = h;
	glViewport(0, 0, w, h);
}

void Engine::engine_display()
{
	GETCORE
	++core->_FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void Engine::engine_idle()
{
#ifndef FPS
	glutPostRedisplay();
#endif // 
}

void Engine::engine_cleanup()
{
	GETCORE
	core->shutdown();
	std::cout << "Closing Window..." << std::endl;
}

void Engine::engine_fpsLimit(int value)
{
#ifdef FPS
	Engine::engine_PostRedisplay();
	glutTimerFunc(1000/FPS, engine_fpsLimit, 0);
#endif
}

void Engine::engine_PostRedisplay() {
	GETCORE
	if (!core->isShutdown()) {
		glutPostRedisplay();
	}
}

void Engine::engine_keyboardInput(unsigned char key, int x, int y)
{
	GETCORE
	switch (key) {
		case 'Q':
		case 'q':
			core->shutdown();
			glutDestroyWindow(_WindowHandle);
			break;
		default:
			break;
	}
}

void Engine::engine_mouseInput(int x, int y)
{
	std::cout << "Mouse Input\n" << "\nint x : " << x << "\nint y : " << y << std::endl;
}

void Engine::engine_CreateScene()
{
	std::cout << "Default Scene" << std::endl;
}
