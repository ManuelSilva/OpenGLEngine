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
		_glutProp.Engine_windowName = "Hello Modern 3D World";

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
	std::cout << "Creating Custom 2D Scene..." << std::endl;
	
	float h[7], c[52];
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(-0.3f, 1.0f);
	std::uniform_real_distribution<> dist2(0.35f, 0.9f);

	for (int n = 0; n < 7; n++) {
		h[n] = dist(e2);
	}
	for (int i = 0; i < 52; i++) {
		c[i] = dist2(e2);
	}

	//CreateScene
	Engine::Scene mainScene = core->_mainScene;
	//------------------------------------------
	

	//triangles---------------------------------------------------------------------------
	//Setup shader to Object
	Engine::GameObject triangle1 = Engine::GameObject(shaderSetUp(), geometryDraw, geometryFunction);
	//------------------------------------------------------
	triangle1.geo.Vertices.push_back(EngineMath::vec4(0.0f, 1.0f, h[0], 1.0f));
	triangle1.geo.Vertices.push_back(EngineMath::vec4(-2.0f, -1.0f, h[0], 1.0f));
	triangle1.geo.Vertices.push_back(EngineMath::vec4(2.0f, -1.0f, h[0], 1.0f));

	triangle1.geo.Vertices.push_back(EngineMath::vec4(0.0f, 1.0f, -.5f, 1.0f));
	triangle1.geo.Vertices.push_back(EngineMath::vec4(-2.0f, -1.0f, -.5f, 1.0f));
	triangle1.geo.Vertices.push_back(EngineMath::vec4(2.0f, -1.0f, -.5f, 1.0f));


	triangle1.objectMatrix = MatrixFactory::TranslationMatrix(EngineMath::vec3(0, -.5f, 0))
							*MatrixFactory::ScaleMatrix(EngineMath::vec3(1 / 2.0f, 1 / 2.0f, 1));

	//------------------------------------------------------------------------------
	Engine::GameObject triangle10 = Engine::duplicateGameObject(triangle1);
	Engine::GameObject triangle11 = Engine::duplicateGameObject(triangle1);
	Engine::GameObject triangle12 = Engine::duplicateGameObject(triangle1);
	Engine::GameObject triangle13 = Engine::duplicateGameObject(triangle1);
	Engine::GameObject triangle14 = Engine::duplicateGameObject(triangle1);
	Engine::GameObject triangle15 = Engine::duplicateGameObject(triangle1);
	Engine::GameObject triangle16 = Engine::duplicateGameObject(triangle1);
	Engine::GameObject triangle17 = Engine::duplicateGameObject(triangle1);

	triangle1.geo.color = Colors::hsv2rgb(10,100,100);

	triangle10.geo.Indexes.push_back(0);
	triangle10.geo.Indexes.push_back(1);
	triangle10.geo.Indexes.push_back(2);

	triangle11.geo.Indexes.push_back(5);
	triangle11.geo.Indexes.push_back(4);
	triangle11.geo.Indexes.push_back(3);

	triangle12.geo.Indexes.push_back(0);
	triangle12.geo.Indexes.push_back(3);
	triangle12.geo.Indexes.push_back(4);

	triangle13.geo.Indexes.push_back(4);
	triangle13.geo.Indexes.push_back(1);
	triangle13.geo.Indexes.push_back(0);

	triangle14.geo.Indexes.push_back(4);
	triangle14.geo.Indexes.push_back(2);
	triangle14.geo.Indexes.push_back(1);

	triangle15.geo.Indexes.push_back(5);
	triangle15.geo.Indexes.push_back(2);
	triangle15.geo.Indexes.push_back(4);

	triangle16.geo.Indexes.push_back(5);
	triangle16.geo.Indexes.push_back(3);
	triangle16.geo.Indexes.push_back(0);

	triangle17.geo.Indexes.push_back(2);
	triangle17.geo.Indexes.push_back(5);
	triangle17.geo.Indexes.push_back(0);

	triangle10.geo.color = Colors::hsv2rgb(0, 1, 1);
	mainScene.push(triangle10);
	triangle11.geo.color = Colors::hsv2rgb(0, c[0], c[1]);
	mainScene.push(triangle11);
	triangle12.geo.color = Colors::hsv2rgb(0, c[2], c[3]);
	mainScene.push(triangle12);
	triangle13.geo.color = Colors::hsv2rgb(0, c[2], c[3]);
	mainScene.push(triangle13);
	triangle14.geo.color = Colors::hsv2rgb(0, c[4], c[5]);
	mainScene.push(triangle14);
	triangle15.geo.color = Colors::hsv2rgb(0, c[4], c[5]);
	mainScene.push(triangle15);
	triangle16.geo.color = Colors::hsv2rgb(0, c[6], c[7]);
	mainScene.push(triangle16);
	triangle17.geo.color = Colors::hsv2rgb(0, c[6], c[7]);
	mainScene.push(triangle17);

	//------------------------------------------------------------------------------

	//-------------------------------------------------------

	Engine::GameObject triangle2 = Engine::duplicateGameObject(triangle1);
	triangle2.geo.color = EngineMath::glVec4(EngineMath::vec4(0, 1, 0, 1)); //green
	triangle2.geo.Vertices[0].z = h[1];
	triangle2.geo.Vertices[1].z = h[1];
	triangle2.geo.Vertices[2].z = h[1];

	triangle2.objectMatrix = MatrixFactory::TranslationMatrix(EngineMath::vec3(-.5f, 0, 0))
							*MatrixFactory::RotationZMatrix(-PI / 2)
							*MatrixFactory::ScaleMatrix(EngineMath::vec3(1 / 2.0f, 1 / 2.0f, 1));

	triangle2.geo.color = Colors::hsv2rgb(100, 100, 100);

	Engine::GameObject triangle20 = Engine::duplicateGameObject(triangle2);
	Engine::GameObject triangle21 = Engine::duplicateGameObject(triangle2);
	Engine::GameObject triangle22 = Engine::duplicateGameObject(triangle2);
	Engine::GameObject triangle23 = Engine::duplicateGameObject(triangle2);
	Engine::GameObject triangle24 = Engine::duplicateGameObject(triangle2);
	Engine::GameObject triangle25 = Engine::duplicateGameObject(triangle2);
	Engine::GameObject triangle26 = Engine::duplicateGameObject(triangle2);
	Engine::GameObject triangle27 = Engine::duplicateGameObject(triangle2);

	triangle20.geo.Indexes.push_back(0);
	triangle20.geo.Indexes.push_back(1);
	triangle20.geo.Indexes.push_back(2);

	triangle21.geo.Indexes.push_back(5);
	triangle21.geo.Indexes.push_back(4);
	triangle21.geo.Indexes.push_back(3);

	triangle22.geo.Indexes.push_back(0);
	triangle22.geo.Indexes.push_back(3);
	triangle22.geo.Indexes.push_back(4);

	triangle23.geo.Indexes.push_back(4);
	triangle23.geo.Indexes.push_back(1);
	triangle23.geo.Indexes.push_back(0);

	triangle24.geo.Indexes.push_back(4);
	triangle24.geo.Indexes.push_back(2);
	triangle24.geo.Indexes.push_back(1);

	triangle25.geo.Indexes.push_back(5);
	triangle25.geo.Indexes.push_back(2);
	triangle25.geo.Indexes.push_back(4);

	triangle26.geo.Indexes.push_back(5);
	triangle26.geo.Indexes.push_back(3);
	triangle26.geo.Indexes.push_back(0);

	triangle27.geo.Indexes.push_back(2);
	triangle27.geo.Indexes.push_back(5);
	triangle27.geo.Indexes.push_back(0);

	triangle20.geo.color = Colors::hsv2rgb(100, 1, 1);
	mainScene.push(triangle20);
	triangle21.geo.color = Colors::hsv2rgb(100, c[8], c[9]);
	mainScene.push(triangle21);
	triangle22.geo.color = Colors::hsv2rgb(100, c[10], c[11]);
	mainScene.push(triangle22);
	triangle23.geo.color = Colors::hsv2rgb(100, c[10], c[11]);
	mainScene.push(triangle23);
	triangle24.geo.color = Colors::hsv2rgb(100, c[12], c[13]);
	mainScene.push(triangle24);
	triangle25.geo.color = Colors::hsv2rgb(100, c[12], c[13]);
	mainScene.push(triangle25);
	triangle26.geo.color = Colors::hsv2rgb(100, c[14], c[15]);
	mainScene.push(triangle26);
	triangle27.geo.color = Colors::hsv2rgb(100, c[14], c[15]);
	mainScene.push(triangle27);

	//-------------------------------------------------------
	Engine::GameObject triangle3 = Engine::duplicateGameObject(triangle1);
	triangle3.geo.color = EngineMath::glVec4(EngineMath::vec4(0, 0, 1, 1)); //blue
	triangle3.geo.Vertices[0].z = h[2];
	triangle3.geo.Vertices[1].z = h[2];
	triangle3.geo.Vertices[2].z = h[2];

	triangle3.objectMatrix = MatrixFactory::TranslationMatrix(EngineMath::vec3(.75f, .75f, 0))
							*MatrixFactory::RotationZMatrix(-0.78539f)
							*MatrixFactory::ScaleMatrix(EngineMath::vec3(0.36f, 0.36f, 1));
							 
	triangle3.geo.color = Colors::hsv2rgb(200,1,1);

	Engine::GameObject triangle30 = Engine::duplicateGameObject(triangle3);
	Engine::GameObject triangle31 = Engine::duplicateGameObject(triangle3);
	Engine::GameObject triangle32 = Engine::duplicateGameObject(triangle3);
	Engine::GameObject triangle33 = Engine::duplicateGameObject(triangle3);
	Engine::GameObject triangle34 = Engine::duplicateGameObject(triangle3);
	Engine::GameObject triangle35 = Engine::duplicateGameObject(triangle3);
	Engine::GameObject triangle36 = Engine::duplicateGameObject(triangle3);
	Engine::GameObject triangle37 = Engine::duplicateGameObject(triangle3);

	triangle30.geo.Indexes.push_back(0);
	triangle30.geo.Indexes.push_back(1);
	triangle30.geo.Indexes.push_back(2);

	triangle31.geo.Indexes.push_back(5);
	triangle31.geo.Indexes.push_back(4);
	triangle31.geo.Indexes.push_back(3);

	triangle32.geo.Indexes.push_back(0);
	triangle32.geo.Indexes.push_back(3);
	triangle32.geo.Indexes.push_back(4);

	triangle33.geo.Indexes.push_back(4);
	triangle33.geo.Indexes.push_back(1);
	triangle33.geo.Indexes.push_back(0);

	triangle34.geo.Indexes.push_back(4);
	triangle34.geo.Indexes.push_back(2);
	triangle34.geo.Indexes.push_back(1);

	triangle35.geo.Indexes.push_back(5);
	triangle35.geo.Indexes.push_back(2);
	triangle35.geo.Indexes.push_back(4);

	triangle36.geo.Indexes.push_back(5);
	triangle36.geo.Indexes.push_back(3);
	triangle36.geo.Indexes.push_back(0);

	triangle37.geo.Indexes.push_back(2);
	triangle37.geo.Indexes.push_back(5);
	triangle37.geo.Indexes.push_back(0);

	triangle30.geo.color = Colors::hsv2rgb(200, 1, 1);
	mainScene.push(triangle30);
	triangle31.geo.color = Colors::hsv2rgb(200, c[16], c[17]);
	mainScene.push(triangle31);
	triangle32.geo.color = Colors::hsv2rgb(200, c[18], c[19]);
	mainScene.push(triangle32);
	triangle33.geo.color = Colors::hsv2rgb(200, c[18], c[19]);
	mainScene.push(triangle33);
	triangle34.geo.color = Colors::hsv2rgb(200, c[20], c[21]);
	mainScene.push(triangle34);
	triangle35.geo.color = Colors::hsv2rgb(200, c[20], c[21]);
	mainScene.push(triangle35);
	triangle36.geo.color = Colors::hsv2rgb(200, c[22], c[23]);
	mainScene.push(triangle36);
	triangle37.geo.color = Colors::hsv2rgb(200, c[22], c[23]);
	mainScene.push(triangle37);

	//-------------------------------------------------------
	Engine::GameObject triangle4 = Engine::duplicateGameObject(triangle1);
	triangle4.geo.color = EngineMath::glVec4(EngineMath::vec4(0, 1, 1, 1)); //green + blue
	triangle4.geo.Vertices[0].z = h[3];
	triangle4.geo.Vertices[1].z = h[3];
	triangle4.geo.Vertices[2].z = h[3];
	
	triangle4.geo.color = Colors::hsv2rgb(37, 1, 1);

	triangle4.objectMatrix = MatrixFactory::ScaleMatrix(EngineMath::vec3(1 / 4.0f, 1 / 4.0f, 1))
							*MatrixFactory::RotationZMatrix(PI)
							*MatrixFactory::TranslationMatrix(EngineMath::vec3(0, -1, 0));


	Engine::GameObject triangle40 = Engine::duplicateGameObject(triangle4);
	Engine::GameObject triangle41 = Engine::duplicateGameObject(triangle4);
	Engine::GameObject triangle42 = Engine::duplicateGameObject(triangle4);
	Engine::GameObject triangle43 = Engine::duplicateGameObject(triangle4);
	Engine::GameObject triangle44 = Engine::duplicateGameObject(triangle4);
	Engine::GameObject triangle45 = Engine::duplicateGameObject(triangle4);
	Engine::GameObject triangle46 = Engine::duplicateGameObject(triangle4);
	Engine::GameObject triangle47 = Engine::duplicateGameObject(triangle4);

	triangle40.geo.Indexes.push_back(0);
	triangle40.geo.Indexes.push_back(1);
	triangle40.geo.Indexes.push_back(2);

	triangle41.geo.Indexes.push_back(5);
	triangle41.geo.Indexes.push_back(4);
	triangle41.geo.Indexes.push_back(3);

	triangle42.geo.Indexes.push_back(0);
	triangle42.geo.Indexes.push_back(3);
	triangle42.geo.Indexes.push_back(4);

	triangle43.geo.Indexes.push_back(4);
	triangle43.geo.Indexes.push_back(1);
	triangle43.geo.Indexes.push_back(0);

	triangle44.geo.Indexes.push_back(4);
	triangle44.geo.Indexes.push_back(2);
	triangle44.geo.Indexes.push_back(1);

	triangle45.geo.Indexes.push_back(5);
	triangle45.geo.Indexes.push_back(2);
	triangle45.geo.Indexes.push_back(4);

	triangle46.geo.Indexes.push_back(5);
	triangle46.geo.Indexes.push_back(3);
	triangle46.geo.Indexes.push_back(0);

	triangle47.geo.Indexes.push_back(2);
	triangle47.geo.Indexes.push_back(5);
	triangle47.geo.Indexes.push_back(0);

	triangle40.geo.color = Colors::hsv2rgb(37, 1, 1);
	mainScene.push(triangle40);
	triangle41.geo.color = Colors::hsv2rgb(37, c[24], c[25]);
	mainScene.push(triangle41);
	triangle42.geo.color = Colors::hsv2rgb(37, c[26], c[27]);
	mainScene.push(triangle42);
	triangle43.geo.color = Colors::hsv2rgb(37, c[26], c[27]);
	mainScene.push(triangle43);
	triangle44.geo.color = Colors::hsv2rgb(37, c[28], c[29]);
	mainScene.push(triangle44);
	triangle45.geo.color = Colors::hsv2rgb(37, c[28], c[29]);
	mainScene.push(triangle45);
	triangle46.geo.color = Colors::hsv2rgb(37, c[30], c[31]);
	mainScene.push(triangle46);
	triangle47.geo.color = Colors::hsv2rgb(37, c[30], c[31]);
	mainScene.push(triangle47);
	
	//-------------------------------------------------------
	Engine::GameObject triangle5 = Engine::duplicateGameObject(triangle1);
	triangle5.geo.color = EngineMath::glVec4(EngineMath::vec4(1, 0, 1, 1)); //red + blue
	triangle5.geo.Vertices[0].z = h[4];
	triangle5.geo.Vertices[1].z = h[4];
	triangle5.geo.Vertices[2].z = h[4];

	triangle5.geo.color = Colors::hsv2rgb(290, 1, 1);


	triangle5.objectMatrix = MatrixFactory::ScaleMatrix(EngineMath::vec3(1 / 4.0f, 1 / 4.0f, 1)) 
							*MatrixFactory::RotationZMatrix(PI / 2)
							*MatrixFactory::TranslationMatrix(EngineMath::vec3(-2.f, -3.f, 0));

	Engine::GameObject triangle50 = Engine::duplicateGameObject(triangle5);
	Engine::GameObject triangle51 = Engine::duplicateGameObject(triangle5);
	Engine::GameObject triangle52 = Engine::duplicateGameObject(triangle5);
	Engine::GameObject triangle53 = Engine::duplicateGameObject(triangle5);
	Engine::GameObject triangle54 = Engine::duplicateGameObject(triangle5);
	Engine::GameObject triangle55 = Engine::duplicateGameObject(triangle5);
	Engine::GameObject triangle56 = Engine::duplicateGameObject(triangle5);
	Engine::GameObject triangle57 = Engine::duplicateGameObject(triangle5);

	triangle50.geo.Indexes.push_back(0);
	triangle50.geo.Indexes.push_back(1);
	triangle50.geo.Indexes.push_back(2);

	triangle51.geo.Indexes.push_back(5);
	triangle51.geo.Indexes.push_back(4);
	triangle51.geo.Indexes.push_back(3);

	triangle52.geo.Indexes.push_back(0);
	triangle52.geo.Indexes.push_back(3);
	triangle52.geo.Indexes.push_back(4);

	triangle53.geo.Indexes.push_back(4);
	triangle53.geo.Indexes.push_back(1);
	triangle53.geo.Indexes.push_back(0);

	triangle54.geo.Indexes.push_back(4);
	triangle54.geo.Indexes.push_back(2);
	triangle54.geo.Indexes.push_back(1);

	triangle55.geo.Indexes.push_back(5);
	triangle55.geo.Indexes.push_back(2);
	triangle55.geo.Indexes.push_back(4);

	triangle56.geo.Indexes.push_back(5);
	triangle56.geo.Indexes.push_back(3);
	triangle56.geo.Indexes.push_back(0);

	triangle57.geo.Indexes.push_back(2);
	triangle57.geo.Indexes.push_back(5);
	triangle57.geo.Indexes.push_back(0);

	triangle50.geo.color = Colors::hsv2rgb(290, 1, 1);
	mainScene.push(triangle50);
	triangle51.geo.color = Colors::hsv2rgb(290, c[24], c[25]);
	mainScene.push(triangle51);
	triangle52.geo.color = Colors::hsv2rgb(290, c[26], c[27]);
	mainScene.push(triangle52);
	triangle53.geo.color = Colors::hsv2rgb(290, c[26], c[27]);
	mainScene.push(triangle53);
	triangle54.geo.color = Colors::hsv2rgb(290, c[28], c[29]);
	mainScene.push(triangle54);
	triangle55.geo.color = Colors::hsv2rgb(290, c[28], c[29]);
	mainScene.push(triangle55);
	triangle56.geo.color = Colors::hsv2rgb(290, c[30], c[31]);
	mainScene.push(triangle56);
	triangle57.geo.color = Colors::hsv2rgb(290, c[30], c[31]);
	mainScene.push(triangle57);
	//-------------------------------------------------------

	//----------------------------------------------------------------------------------------------------
	
	Engine::GameObject square = Engine::GameObject(shaderSetUp(), geometryDraw, geometryFunction);

	square.geo.Vertices.push_back(EngineMath::vec4(0.0f,1.0f, h[5],1.0f));
	square.geo.Vertices.push_back(EngineMath::vec4(-1.0f,0.0f, h[5],1.0f));
	square.geo.Vertices.push_back(EngineMath::vec4(.0f,-1.0f, h[5],1.0f));
	square.geo.Vertices.push_back(EngineMath::vec4(1.0f,.0f, h[5],1.0f));

	square.geo.Vertices.push_back(EngineMath::vec4(0.0f, 1.0f, -.5f, 1.0f));
	square.geo.Vertices.push_back(EngineMath::vec4(-1.0f, 0.0f, -.5f, 1.0f));
	square.geo.Vertices.push_back(EngineMath::vec4(.0f, -1.0f, -.5f, 1.0f));
	square.geo.Vertices.push_back(EngineMath::vec4(1.0f, .0f, -.5f, 1.0f));

	square.objectMatrix = MatrixFactory::ScaleMatrix(EngineMath::vec3(1 / 2.0f, 1 / 2.0f,1))
						 *MatrixFactory::TranslationMatrix(EngineMath::vec3(1, 0, 0));

	square.geo.color = Colors::hsv2rgb(60,1,1); 

	Engine::GameObject square1 = Engine::duplicateGameObject(square);
	Engine::GameObject square2 = Engine::duplicateGameObject(square);
	Engine::GameObject square3 = Engine::duplicateGameObject(square);
	Engine::GameObject square4 = Engine::duplicateGameObject(square);
	Engine::GameObject square5 = Engine::duplicateGameObject(square);
	Engine::GameObject square6 = Engine::duplicateGameObject(square);
	Engine::GameObject square7 = Engine::duplicateGameObject(square);
	Engine::GameObject square8 = Engine::duplicateGameObject(square);
	Engine::GameObject square9 = Engine::duplicateGameObject(square);
	Engine::GameObject square10 = Engine::duplicateGameObject(square);
	Engine::GameObject square11 = Engine::duplicateGameObject(square);
	Engine::GameObject square12 = Engine::duplicateGameObject(square);


	square1.geo.Indexes.push_back(0);
	square1.geo.Indexes.push_back(1);
	square1.geo.Indexes.push_back(3);

	square2.geo.Indexes.push_back(1);
	square2.geo.Indexes.push_back(2);
	square2.geo.Indexes.push_back(3);

	square3.geo.Indexes.push_back(7);
	square3.geo.Indexes.push_back(5);
	square3.geo.Indexes.push_back(4);

	square4.geo.Indexes.push_back(7);
	square4.geo.Indexes.push_back(6);
	square4.geo.Indexes.push_back(5);

	square5.geo.Indexes.push_back(4);
	square5.geo.Indexes.push_back(0);
	square5.geo.Indexes.push_back(7);

	square6.geo.Indexes.push_back(0);
	square6.geo.Indexes.push_back(3);
	square6.geo.Indexes.push_back(7);

	square7.geo.Indexes.push_back(0);
	square7.geo.Indexes.push_back(4);
	square7.geo.Indexes.push_back(5);

	square8.geo.Indexes.push_back(0);
	square8.geo.Indexes.push_back(5);
	square8.geo.Indexes.push_back(1);

	square9.geo.Indexes.push_back(3);
	square9.geo.Indexes.push_back(6);
	square9.geo.Indexes.push_back(7);

	square10.geo.Indexes.push_back(3);
	square10.geo.Indexes.push_back(2);
	square10.geo.Indexes.push_back(6);

	square11.geo.Indexes.push_back(1);
	square11.geo.Indexes.push_back(5);
	square11.geo.Indexes.push_back(6);

	square12.geo.Indexes.push_back(1);
	square12.geo.Indexes.push_back(6);
	square12.geo.Indexes.push_back(2);

	square1.geo.color = Colors::hsv2rgb(60, 1, 1);
	mainScene.push(square1);
	square2.geo.color = Colors::hsv2rgb(60, 1, 1);
	mainScene.push(square2);
	square3.geo.color = Colors::hsv2rgb(60, c[32], c[33]);
	mainScene.push(square3);
	square4.geo.color = Colors::hsv2rgb(60, c[32], c[33]);
	mainScene.push(square4);
	square5.geo.color = Colors::hsv2rgb(60, c[34], c[35]);
	mainScene.push(square5);
	square6.geo.color = Colors::hsv2rgb(60, c[34], c[35]);
	mainScene.push(square6);
	square7.geo.color = Colors::hsv2rgb(60, c[36], c[37]);
	mainScene.push(square7);
	square8.geo.color = Colors::hsv2rgb(60, c[36], c[37]);
	mainScene.push(square8);
	square9.geo.color = Colors::hsv2rgb(60, c[38], c[39]);
	mainScene.push(square9);
	square10.geo.color = Colors::hsv2rgb(60, c[38], c[39]);
	mainScene.push(square10);
	square11.geo.color = Colors::hsv2rgb(60, c[40], c[41]);
	mainScene.push(square11);
	square12.geo.color = Colors::hsv2rgb(60, c[40], c[41]);
	mainScene.push(square12);




	//----------------------------------------------------------------------------------------------------
	Engine::GameObject paralelogram = Engine::GameObject(shaderSetUp(), geometryDraw, geometryFunction);

	paralelogram.geo.Vertices.push_back(EngineMath::vec4(-3.0f, 1.0f, h[6], 1.0f));
	paralelogram.geo.Vertices.push_back(EngineMath::vec4(-1.0f, -1.f, h[6], 1.0f));
	paralelogram.geo.Vertices.push_back(EngineMath::vec4(3.0f, -1.0f, h[6], 1.0f));
	paralelogram.geo.Vertices.push_back(EngineMath::vec4(1.0f, 1.0f,  h[6], 1.0f));

	paralelogram.geo.Vertices.push_back(EngineMath::vec4(-3.0f, 1.0f, -.5f, 1.0f));
	paralelogram.geo.Vertices.push_back(EngineMath::vec4(-1.0f, -1.f, -.5f, 1.0f));
	paralelogram.geo.Vertices.push_back(EngineMath::vec4(3.0f, -1.0f, -.5f, 1.0f));
	paralelogram.geo.Vertices.push_back(EngineMath::vec4(1.0f, 1.0f, -.5f, 1.0f));

	paralelogram.geo.color = Colors::hsv2rgb(152,1,1);

	paralelogram.objectMatrix = MatrixFactory::ScaleMatrix(EngineMath::vec3(1 / 4.0f, 1 / 4.0f, 1))
								*MatrixFactory::TranslationMatrix(EngineMath::vec3(-1, 3, 0));

	Engine::GameObject paralelogram1 = Engine::duplicateGameObject(paralelogram);
	Engine::GameObject paralelogram2 = Engine::duplicateGameObject(paralelogram);
	Engine::GameObject paralelogram3 = Engine::duplicateGameObject(paralelogram);
	Engine::GameObject paralelogram4 = Engine::duplicateGameObject(paralelogram);
	Engine::GameObject paralelogram5 = Engine::duplicateGameObject(paralelogram);
	Engine::GameObject paralelogram6 = Engine::duplicateGameObject(paralelogram);
	Engine::GameObject paralelogram7 = Engine::duplicateGameObject(paralelogram);
	Engine::GameObject paralelogram8 = Engine::duplicateGameObject(paralelogram);
	Engine::GameObject paralelogram9 = Engine::duplicateGameObject(paralelogram);
	Engine::GameObject paralelogram10 = Engine::duplicateGameObject(paralelogram);
	Engine::GameObject paralelogram11 = Engine::duplicateGameObject(paralelogram);
	Engine::GameObject paralelogram12 = Engine::duplicateGameObject(paralelogram);

	paralelogram1.geo.Indexes.push_back(0);
	paralelogram1.geo.Indexes.push_back(1);
	paralelogram1.geo.Indexes.push_back(3);

	paralelogram2.geo.Indexes.push_back(1);
	paralelogram2.geo.Indexes.push_back(2);
	paralelogram2.geo.Indexes.push_back(3);

	paralelogram3.geo.Indexes.push_back(7);
	paralelogram3.geo.Indexes.push_back(5);
	paralelogram3.geo.Indexes.push_back(4);

	paralelogram4.geo.Indexes.push_back(7);
	paralelogram4.geo.Indexes.push_back(6);
	paralelogram4.geo.Indexes.push_back(5);

	paralelogram5.geo.Indexes.push_back(4);
	paralelogram5.geo.Indexes.push_back(0);
	paralelogram5.geo.Indexes.push_back(7);

	paralelogram6.geo.Indexes.push_back(0);
	paralelogram6.geo.Indexes.push_back(3);
	paralelogram6.geo.Indexes.push_back(7);

	paralelogram7.geo.Indexes.push_back(0);
	paralelogram7.geo.Indexes.push_back(4);
	paralelogram7.geo.Indexes.push_back(5);

	paralelogram8.geo.Indexes.push_back(0);
	paralelogram8.geo.Indexes.push_back(5);
	paralelogram8.geo.Indexes.push_back(1);

	paralelogram9.geo.Indexes.push_back(3);
	paralelogram9.geo.Indexes.push_back(6);
	paralelogram9.geo.Indexes.push_back(7);

	paralelogram10.geo.Indexes.push_back(3);
	paralelogram10.geo.Indexes.push_back(2);
	paralelogram10.geo.Indexes.push_back(6);

	paralelogram11.geo.Indexes.push_back(1);
	paralelogram11.geo.Indexes.push_back(5);
	paralelogram11.geo.Indexes.push_back(6);

	paralelogram12.geo.Indexes.push_back(1);
	paralelogram12.geo.Indexes.push_back(6);
	paralelogram12.geo.Indexes.push_back(2);

	paralelogram1.geo.color = Colors::hsv2rgb(152, 1, 1);
	mainScene.push(paralelogram1);
	paralelogram2.geo.color = Colors::hsv2rgb(152, 1, 1);
	mainScene.push(paralelogram2);
	paralelogram3.geo.color = Colors::hsv2rgb(152, c[42], c[43]);
	mainScene.push(paralelogram3);
	paralelogram4.geo.color = Colors::hsv2rgb(152, c[42], c[43]);
	mainScene.push(paralelogram4);
	paralelogram5.geo.color = Colors::hsv2rgb(152, c[44], c[45]);
	mainScene.push(paralelogram5);
	paralelogram6.geo.color = Colors::hsv2rgb(152, c[44], c[45]);
	mainScene.push(paralelogram6);
	paralelogram7.geo.color = Colors::hsv2rgb(152, c[46], c[47]);
	mainScene.push(paralelogram7);
	paralelogram8.geo.color = Colors::hsv2rgb(152, c[46], c[47]);
	mainScene.push(paralelogram8);
	paralelogram9.geo.color = Colors::hsv2rgb(152, c[48], c[49]);
	mainScene.push(paralelogram9);
	paralelogram10.geo.color = Colors::hsv2rgb(152, c[48], c[49]);
	mainScene.push(paralelogram10);
	paralelogram11.geo.color = Colors::hsv2rgb(152, c[50], c[51]);
	mainScene.push(paralelogram11);
	paralelogram12.geo.color = Colors::hsv2rgb(152, c[50], c[51]);
	mainScene.push(paralelogram12);

	mainScene.push(paralelogram);
	

	//----------------------------------------------------------------------------------------------------


	float aspect = (core->_Active_GLUT_Properties.Engine_windowSize_x*1.0f) / (core->_Active_GLUT_Properties.Engine_windowSize_y*1.0f);
	_mainCamera.setPerspective(30, aspect, .1f, 10);
	_mainCamera.eyeVector = EngineMath::vec3(0,0,3);

	core->_mainScene = mainScene;
	std::cout << "Success Creating Scene!" << std::endl;
}

void geometryFunction(Engine::GameObject obj) {
	GETCORE
	GLuint VaoId;
	GLuint VboId[3];
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		glGenBuffers(2, VboId);

		glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
		glBufferData(GL_ARRAY_BUFFER, obj.geo.Vertices.size() * sizeof(EngineMath::vec4), obj.geo.Vertices.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(EngineMath::vec4), 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj.geo.Indexes.size()*sizeof(GLubyte), obj.geo.Indexes.data(), GL_STATIC_DRAW);
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//need to make sure reference to VAO and VBO is not destroyed with temp Object!!
	core->_mainScene._gameObjects[obj.uniqueId].geo.VaoId = VaoId;
	core->_mainScene._gameObjects[obj.uniqueId].geo.VboId[0] = VboId[0];
	core->_mainScene._gameObjects[obj.uniqueId].geo.VboId[1] = VboId[1];
	core->_mainScene._gameObjects[obj.uniqueId].geo.VboId[2] = VboId[2];
	core->checkOpenGLError("ERROR: Could not create VAOs and VBOs.");}

void geometryDraw(Engine::GameObject obj) {
	GETCORE
	//need to make sure reference to VAO and VBO is not destroyed with temp Object!!
	GLuint VaoId = core->_mainScene._gameObjects[obj.uniqueId].geo.VaoId;
	glBindVertexArray(VaoId);
	obj._prog.bind();
	glUniformMatrix4fv(obj._prog.getUniformLocation("Matrix").getGLHandle(), 1, GL_FALSE, obj.modalMatrix.m);
	glUniform4fv(obj._prog.getUniformLocation("ColorStatic").getGLHandle(), 1, obj.geo.color.xyzw);
	glDrawElements(GL_TRIANGLES, obj.geo.Indexes.size(), GL_UNSIGNED_BYTE, (GLvoid*)0);
	obj._prog.unBind();
	glBindVertexArray(0);
	core->checkOpenGLError("ERROR: Could not draw scene.");}

Engine::Shader shaderSetUp() {	
	GETCORE
	Engine::Shader shaderProg = shaderProg;
	std::string path = SHADER_PATH;
	path.append("hello2DWorld.vert");
	shaderProg.loadFromFile(GL_VERTEX_SHADER, path.c_str());
	path = SHADER_PATH;
	path.append("hello2DWorld.frag");
	shaderProg.loadFromFile(GL_FRAGMENT_SHADER, path.c_str());
	shaderProg.createAndLink();
	shaderProg.setUniform("Matrix");
	shaderProg.setUniform("ColorStatic");
	core->checkOpenGLError("Creating Shader Error");
	return shaderProg;
}
