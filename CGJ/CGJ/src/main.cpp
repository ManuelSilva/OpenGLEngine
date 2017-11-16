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
		core->setUpMouseFunc(mouseInput);

		core->startEngine(argc,argv);

		WAIT
}


void render() {
	GETCORE
	_mainCamera.ApplyViewMatrix();
	update(core->getDeltaTime());
	++core->_FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	core->_mainScene.draw(_mainCamera);
	glutSwapBuffers();}

void update(float delta)
{
	GETCORE
	float aspect = (core->_Active_GLUT_Properties.Engine_windowSize_x*1.0f) / (core->_Active_GLUT_Properties.Engine_windowSize_y*1.0f);
	static bool isOrtho = false;
	float speed = 10.f;
	
	static bool flag = false;
	
	Engine::Scene scene = core->_mainScene;
	//--------------------------------------------
	{
		//engine_keyboardInput
		//initKeyboard


		if (core->keyboard_state['+']) {
			if (!isOrtho) {
				_mainCamera.eyeVector -= EngineMath::vec3(0, 0, speed*delta);
			}
			else {
				_mainCamera.orthoScaleFactor += speed*delta;
			}
			_mainCamera._viewDirty = true;
		}
		if (core->keyboard_state['-']) {
			if (!isOrtho) {
				_mainCamera.eyeVector += EngineMath::vec3(0, 0, speed*delta);
			}
			else {
				_mainCamera.orthoScaleFactor -= speed*delta;
			}
			_mainCamera._viewDirty = true;
		}
		float sensitivity = 1.0f;
		if (!_mainCamera.gimbalLock) {
			sensitivity = 100.0f;
		}
		if (core->keyboard_state['w']) {
			_mainCamera.pitch += delta*sensitivity;
			_mainCamera._viewDirty = true;
		}
		if (core->keyboard_state['s']) {
			_mainCamera.pitch -= delta * sensitivity;
			_mainCamera._viewDirty = true;
		}
		if (core->keyboard_state['a']) {
			_mainCamera.yaw += delta * sensitivity;
			_mainCamera._viewDirty = true;
		}
		if (core->keyboard_state['d']) {
			_mainCamera.yaw -= delta * sensitivity;
			_mainCamera._viewDirty = true;
		}
		if (core->keyboard_state['p']) {
			isOrtho = !isOrtho;
			if (isOrtho) {
				_mainCamera.setOrtho(100, -100, -100, 100, -100, 100);
				_mainCamera.orthoScaleFactor = 14*speed*delta;
			}
			else {
				_mainCamera.setPerspective(30, aspect, .1f, 100);
			}
		}
		if (core->keyboard_state['g']) {
			_mainCamera.gimbalLock = !_mainCamera.gimbalLock;
		}
		if (core->keyboard_state['x']) {
			if (flag) {
				for (std::map<unsigned int, Engine::GameObject>::iterator it = scene._gameObjects.begin(); it != scene._gameObjects.end(); ++it)
				{
					Engine::GameObject obj = it->second;
					if (obj.tag == "Animate") {
						obj.animationInfo.rate = 1 - obj.animationInfo.rate;
						EngineMath::vec3 aux = obj.animationInfo.target_position;
						obj.animationInfo.target_position = obj.animationInfo.initial_position;
						obj.animationInfo.initial_position = aux;
						scene._gameObjects[obj.uniqueId] = obj;
					}
				}
			}
			flag = true;

		}
		if (core->keyboard_state['m']) {
			core->mouseFlag = !core->mouseFlag;
		}
		
		core->initKeyboard();
	}
	//---------------------------------------------

	if (flag) {
		for (std::map<unsigned int, Engine::GameObject>::iterator it = scene._gameObjects.begin(); it != scene._gameObjects.end(); ++it)
		{
			Engine::GameObject obj = it->second;
			if (obj.tag == "Animate") {
				animate(obj);
			}
		}
	}

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
	float deltaMouseY = float(cy - gMouseY)/10;
	float sensitivity = 1.0f;
	if (core->mouseFlag) {

		if (!_mainCamera.gimbalLock) {
			sensitivity = 5.f;
		}
		if (abs(deltaMouseX) > 0.5f)
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
}

void createScene() {
	GETCORE
	std::cout << "Creating Custom Scene..." << std::endl;
	
	//CreateScene
	Engine::Scene mainScene = core->_mainScene;
	//------------------------------------------


	Engine::GameObject floor = Engine::GameObject(shaderSetUp(), geometryDraw, geometryFunction);
	floor.geo = Mesh::createMesh(std::string(OBJ_PATH) + std::string("cube_vn.obj"));
	floor.push(MatrixFactory::ScaleMatrix(EngineMath::vec3(15,15,.5)),false);
	floor.push(MatrixFactory::ScaleMatrix(EngineMath::vec3(.2, .2, .2)) * MatrixFactory::TranslationMatrix(EngineMath::vec3(0, 0, -3)), true);
	floor.tag = "Floor";
	

	Engine::GameObject cube = Engine::GameObject(shaderSetUp(), geometryDraw, geometryFunction);
	cube.geo = Mesh::createMesh(std::string(OBJ_PATH) + std::string("cube_vn.obj"));
	cube.setParent(floor);
	cube.push(MatrixFactory::TranslationMatrix(EngineMath::vec3(0, 3, 1.8)), true);


	Engine::GameObject paralelogram = Engine::GameObject(shaderSetUp(), geometryDraw, geometryFunction);
	paralelogram.geo = Mesh::createMesh(std::string(OBJ_PATH) + std::string("shape2.obj"));
	paralelogram.setParent(floor);
	paralelogram.push(MatrixFactory::TranslationMatrix(EngineMath::vec3(0, -3, 1.8)) * MatrixFactory::RotationXMatrix(PI / 2) * MatrixFactory::RotationYMatrix(PI / 2), true);
	


	Engine::GameObject triangle1 = Engine::GameObject(shaderSetUp(), geometryDraw, geometryFunction);
	triangle1.geo = Mesh::createMesh(std::string(OBJ_PATH) + std::string("triangle.obj"));
	triangle1.setParent(floor);
	triangle1.push(MatrixFactory::TranslationMatrix(EngineMath::vec3(0, 0, 1.8)) * MatrixFactory::RotationXMatrix(PI/2), true);
	Engine::GameObject triangle2 = Engine::duplicateGameObject(triangle1);
	Engine::GameObject triangle3 = Engine::duplicateGameObject(triangle1);
	Engine::GameObject triangle4 = Engine::duplicateGameObject(triangle1);
	Engine::GameObject triangle5 = Engine::duplicateGameObject(triangle1);

	triangle2.push(MatrixFactory::TranslationMatrix(EngineMath::vec3(-3, -3, 0)), true);
	triangle3.push(MatrixFactory::TranslationMatrix(EngineMath::vec3(-2, -5, 0)) * MatrixFactory::ScaleMatrix(EngineMath::vec3(2, 2, 1)) * MatrixFactory::RotationZMatrix(-PI/4), true);
	triangle4.push(MatrixFactory::TranslationMatrix(EngineMath::vec3(1, 5, 0)) * MatrixFactory::ScaleMatrix(EngineMath::vec3(3, 3, 1)) * MatrixFactory::RotationZMatrix((PI*3)/4), true);
	triangle5.push(MatrixFactory::TranslationMatrix(EngineMath::vec3(6, 0, 0)) * MatrixFactory::ScaleMatrix(EngineMath::vec3(3, 3, 1))  * MatrixFactory::RotationZMatrix(PI/4), true);

	triangle5.tag = "Animate";
	triangle5.animationInfo.target_position = EngineMath::vec3(5,2,0);


	mainScene.push(floor);
	//mainScene.push(cube);
	//mainScene.push(paralelogram);

	//mainScene.push(triangle1);
	//mainScene.push(triangle2);
	//mainScene.push(triangle3);
	//mainScene.push(triangle4);
	mainScene.push(triangle5);

	//----------------------------------------------------------------------------------------------------




	//----------------------------------------------------------------------------------------------------


	float aspect = (core->_Active_GLUT_Properties.Engine_windowSize_x*1.0f) / (core->_Active_GLUT_Properties.Engine_windowSize_y*1.0f);
	_mainCamera.setPerspective(30, aspect, .1f, 100);
	_mainCamera.eyeVector = EngineMath::vec3(0,0,5);

	core->_mainScene = mainScene;
	std::cout << "Success Creating Scene!" << std::endl;
}

void geometryFunction(Engine::GameObject obj) {
	GETCORE

	glGenVertexArrays(1, &obj.geo.VaoId);
	glBindVertexArray(obj.geo.VaoId);
	{
		glGenBuffers(1, &obj.geo.VboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, obj.geo.VboVertices);
		glBufferData(GL_ARRAY_BUFFER, obj.geo.Vertices.size() * sizeof(EngineMath::vec3), &obj.geo.Vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(EngineMath::vec3), 0);

		if (obj.geo.TexcoordsLoaded)
		{
			glGenBuffers(1, &obj.geo.VboTexcoords);
			glBindBuffer(GL_ARRAY_BUFFER, obj.geo.VboTexcoords);
			glBufferData(GL_ARRAY_BUFFER, obj.geo.Texcoords.size() * sizeof(EngineMath::vec2), &obj.geo.Texcoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXCOORDS);
			glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(EngineMath::vec2), 0);
		}
		if (obj.geo.NormalsLoaded)
		{
			glGenBuffers(1, &obj.geo.VboNormals);
			glBindBuffer(GL_ARRAY_BUFFER, obj.geo.VboNormals);
			glBufferData(GL_ARRAY_BUFFER, obj.geo.Normals.size() * sizeof(EngineMath::vec3), &obj.geo.Normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMALS);
			glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(EngineMath::vec3), 0);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	core->_mainScene._gameObjects[obj.uniqueId].geo = obj.geo;

	core->checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void geometryDraw(Engine::GameObject obj) {
	GETCORE

	glBindVertexArray(obj.geo.VaoId);

	obj._prog.bind();

	glUniformMatrix4fv(obj._prog.getUniformLocation("ModelMatrix").getGLHandle(), 1, GL_FALSE, Engine::getModelMatrix(core->_mainScene, obj).m);
	glUniformMatrix4fv(obj._prog.getUniformLocation("ViewMatrix").getGLHandle(), 1, GL_FALSE, _mainCamera.getViewMatrix().m);
	glUniformMatrix4fv(obj._prog.getUniformLocation("ProjectionMatrix").getGLHandle(), 1, GL_FALSE, _mainCamera.getProjectionMatrix().m);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)obj.geo.Vertices.size());

	glUseProgram(0);
	glBindVertexArray(0);

	core->checkOpenGLError("ERROR: Could not draw scene.");
}

Engine::Shader shaderSetUp() {	
	GETCORE
	
	Engine::Shader shaderProg;
	std::string path = SHADER_PATH;
	path.append("cube_vs.glsl");
	shaderProg.loadFromFile(GL_VERTEX_SHADER, path.c_str());
	path = SHADER_PATH;
	path.append("cube_fs.glsl");
	shaderProg.loadFromFile(GL_FRAGMENT_SHADER, path.c_str());
	shaderProg.createAndLink();

	shaderProg.setAttribute("inPosition");
	shaderProg.setAttribute("inNormal");

	//if (TexcoordsLoaded)
	//	glBindAttribLocation(ProgramId, TEXCOORDS, "inTexcoord");
	//if (NormalsLoaded)
		//glBindAttribLocation(ProgramId, NORMALS, "inNormal");

	shaderProg.setUniform("ModelMatrix");
	shaderProg.setUniform("ViewMatrix");
	shaderProg.setUniform("ProjectionMatrix");

	core->checkOpenGLError("ERROR: Could not create shaders.");
	return shaderProg;
}

void animate(Engine::GameObject obj)
{
	GETCORE

	Engine::AnimationInfo info = obj.animationInfo;
	if (info.rate < 1.00f) {
		EngineMath::vec3 lerp = EngineMath::lerp(info.initial_position, info.target_position, info.rate);
		obj.push(MatrixFactory::TranslationMatrix(lerp - info.prevLerp),true);
		info.prevLerp = lerp;
		info.rate += core->getDeltaTime();
	}
	else {
		info.rate = 1.00f;
	}
	
	// do the same for rotation


	obj.animationInfo = info;
	core->_mainScene._gameObjects[obj.uniqueId] = obj;
}




