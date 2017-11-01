#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <vector>
#include "../Math/Math.h"

#define MAX_STACK_HISTORY 0

namespace Engine{

	class Camera{
		private:		

			bool isOrtho;

			EngineMath::mat4 _viewMatrix;
			EngineMath::mat4 _projectionMatrix;
			EngineMath::Quaternion camera_q;
		private:
			void UpdateViewMatrix();

		public:
			bool gimbalLock = true;
			float orthoScaleFactor = 5;
			bool _viewDirty;
			float roll = .0f, pitch=.0f, yaw=.0f;
			EngineMath::vec3 eyeVector = EngineMath::vec3(0,0,1);
		public:
			Camera(EngineMath::mat4 cameraMatrix);

			~Camera();

			EngineMath::mat4 getViewMatrix();

			EngineMath::mat4 getProjectionMatrix();


			void setPerspective(float fov, float aspectRatio, float zNear, float zFar);

			void setOrtho(float left, float right, float up, float bottom, float near, float far);

			void ApplyViewMatrix();
			
	};


}

#endif