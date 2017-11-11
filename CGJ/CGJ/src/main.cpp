#include "main.h"

int main(int argc, char* argv[])
{
	GETCORE //gets core - engine singleton instance
		std::cout << "Starting Engine" << std::endl;
	#ifdef _DEBUG
		std::cout << "Debug_Mode" << std::endl;
	#endif 

		Engine::Engine_GLUT_Properties _glutProp;
		_glutProp.Engine_OpenGL_Version = 3;
		_glutProp.Engine_OpenGL_SubVersion = 3;
		_glutProp.Engine_windowSize_x = 500;
		_glutProp.Engine_windowSize_y = 500;
		_glutProp.Engine_windowName = "Final Individual Delivery";

		core->_Active_GLUT_Properties = _glutProp;

		core->setUpRenderFunc(render);
		core->setUpSceneCreateFunc(createScene);
		core->setUpKeyboardFunc(keyboardInput);
		core->setUpMouseFunc(mouseInput);

		core->startEngine(argc,argv);

		WAIT
}


void render() {
	GETCORE
	update(core->getDeltaTime());
	++core->_FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	core->_mainScene.draw(_mainCamera);
	glutSwapBuffers();}

void update(float delta)
{
	GETCORE
	_mainCamera.ApplyViewMatrix();
}

//-----------------------------------------------------

void mouseInput(int x, int y){
	GETCORE
	int gMouseX = x;
	int gMouseY = y;


	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	int cx = (width>>1);
	int cy = (height>>1);


	float deltaMouseX = float(cx - gMouseX)/10;
	float deltaMouseY = float(cy - gMouseY);
	float sensitivity = 1.0f;
	if (!_mainCamera.gimbalLock) {
		sensitivity = 10.f;
	}
	if (abs(deltaMouseX) > .5f)
	{
		glutWarpPointer(cx, y);
		_mainCamera.yaw += deltaMouseX*core->getDeltaTime()*sensitivity;
		_mainCamera._viewDirty = true;
	}
	if (abs(deltaMouseY) > 0.5f) {
		glutWarpPointer(x, cy);
		_mainCamera.pitch += deltaMouseY*core->getDeltaTime()*sensitivity;
		_mainCamera._viewDirty = true;
	}
}

void keyboardInput(unsigned char key, int x, int y)
{
	GETCORE
	float delta = core->getDeltaTime();
	float aspect = (core->_Active_GLUT_Properties.Engine_windowSize_x*1.0f) / (core->_Active_GLUT_Properties.Engine_windowSize_y*1.0f);
	static bool isOrtho = false;
	float speed = 1.f;
	switch (key) {

		case 'W':
		case 'w':
			if (!isOrtho) {
				_mainCamera.eyeVector -= EngineMath::vec3(0, 0, speed*delta);
			}
			else {
				_mainCamera.orthoScaleFactor += speed*delta;
			}
				_mainCamera._viewDirty = true;
			break;
		case 'S':
		case 's':
			if(!isOrtho) {
				_mainCamera.eyeVector += EngineMath::vec3(0, 0, speed*delta);
			}
			else {
				_mainCamera.orthoScaleFactor -= speed*delta;
			}
			_mainCamera._viewDirty = true;
			break;
		case 'A':
		case 'a':
			break;
		case 'D':
		case 'd':
			break;
		case 'E':
		case 'e':
			break;
		case 'Q':
		case 'q':
			break;
		case 'P':
		case 'p':
			isOrtho = !isOrtho;
			if (isOrtho) {
				_mainCamera.setOrtho(10,-10,-10,10,-10,10);
			}
			else {
				_mainCamera.setPerspective(30, aspect, .1f, 10);
			}

			break;
		case 'G':
		case 'g':
			_mainCamera.gimbalLock = !_mainCamera.gimbalLock;
			break;
		case 'X':
		case 'x':
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void createScene() {
	GETCORE
	std::cout << "Creating Custom Scene..." << std::endl;
	
	//CreateScene
	Engine::Scene mainScene = core->_mainScene;
	//------------------------------------------
	
	



	//----------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------------


	float aspect = (core->_Active_GLUT_Properties.Engine_windowSize_x*1.0f) / (core->_Active_GLUT_Properties.Engine_windowSize_y*1.0f);
	_mainCamera.setPerspective(30, aspect, .1f, 10);
	_mainCamera.eyeVector = EngineMath::vec3(0,0,3);

	core->_mainScene = mainScene;
	std::cout << "Success Creating Scene!" << std::endl;
}

void geometryFunction(Engine::GameObject obj) {

}

void geometryDraw(Engine::GameObject obj) {

}

Engine::Shader shaderSetUp() {	
	Engine::Shader prog = Engine::Shader();
	return prog;
}
