#include "camera.h"

void Engine::Camera::UpdateViewMatrix()
{

	if (_viewDirty && gimbalLock) {
		_viewDirty = false;


		EngineMath::mat4 matRoll = MatrixFactory::identity();
		EngineMath::mat4 matPitch = MatrixFactory::identity();
		EngineMath::mat4 matYaw = MatrixFactory::identity();

		matRoll = MatrixFactory::RodriguezMatrix(EngineMath::vec3(0.0f, 0.0f, 1.0f), roll);
		matPitch = MatrixFactory::RodriguezMatrix(EngineMath::vec3(1.0f, 0.0f, 0.0f), pitch);
		matYaw = MatrixFactory::RodriguezMatrix(EngineMath::vec3(0.0f, 1.0f, 0.0f), yaw);

		matRoll.m[15] = 1;
		matPitch.m[15] = 1;
		matYaw.m[15] = 1;

		EngineMath::mat4 orthoScale = MatrixFactory::identity();
		if (isOrtho) {
			orthoScale = MatrixFactory::ScaleMatrix(EngineMath::vec3(orthoScaleFactor, orthoScaleFactor, orthoScaleFactor));
		}

		EngineMath::mat4 rotate = matRoll * matPitch * matYaw;

		EngineMath::mat4 translate = MatrixFactory::identity();
		translate = MatrixFactory::TranslationMatrix(-eyeVector);
	
		_viewMatrix = translate * rotate * orthoScale;
	}

	if (_viewDirty && !gimbalLock) {
		_viewDirty = false;

		EngineMath::Quaternion quat = EngineMath::normalize(EngineMath::Quaternion(roll, EngineMath::vec4(0, 0, 1, 1)) 
															* EngineMath::Quaternion(pitch,EngineMath::vec4(1,0,0,1)) 
															* EngineMath::Quaternion(yaw, EngineMath::vec4(0, 1, 0, 1)));


		EngineMath::mat4 orthoScale = MatrixFactory::identity();
		if (isOrtho) {
			orthoScale = MatrixFactory::ScaleMatrix(EngineMath::vec3(orthoScaleFactor, orthoScaleFactor, orthoScaleFactor));
		}
		pitch = yaw = roll = 0;
		
		camera_q = EngineMath::normalize(quat * camera_q);
		EngineMath::mat4 rotate = camera_q.getMat();
		EngineMath::mat4 translate = MatrixFactory::identity();
		translate = MatrixFactory::TranslationMatrix(-eyeVector);

		_viewMatrix = translate * rotate * orthoScale;
	}
}

Engine::Camera::Camera(EngineMath::mat4 cameraMatrix)
{
	_projectionMatrix = cameraMatrix;
	_viewDirty = true;
	gimbalLock = false;
	orthoScaleFactor = 5;

}

Engine::Camera::~Camera()
{
}

EngineMath::mat4 Engine::Camera::getViewMatrix()
{
	return _viewMatrix;
}

EngineMath::mat4 Engine::Camera::getProjectionMatrix()
{

	return _projectionMatrix;
}

void Engine::Camera::setPerspective(float fov, float aspectRatio, float zNear, float zFar)
{
	isOrtho = false;
	_viewDirty = true;
	_projectionMatrix = MatrixFactory::PerspectiveMatrix(fov, aspectRatio, zNear, zFar);
}

void Engine::Camera::setOrtho(float left, float right, float up, float bottom, float near, float far)
{
	isOrtho = true;
	_viewDirty = true;
	_projectionMatrix = MatrixFactory::OrthographicMatrix(left, right, up, bottom, near, far);
}

void Engine::Camera::ApplyViewMatrix()
{
	UpdateViewMatrix();
}
