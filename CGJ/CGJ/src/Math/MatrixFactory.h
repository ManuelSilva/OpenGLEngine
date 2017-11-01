#ifndef __MATRIX_FACTOTORY_H__
#define __MATRIX_FACTOTORY_H__
	#ifndef __ENGINE_MATH_H__
	#include "Math.h"
	#endif

static unsigned int id_tracker;

namespace MatrixFactory {

	 EngineMath::mat4 identity();

	 EngineMath::mat4 TranslationMatrix(const  EngineMath::vec3 v3);

	 EngineMath::mat4 RotationXMatrix(const float teta);

	 EngineMath::mat4 RotationYMatrix(const float teta);

	 EngineMath::mat4 RotationZMatrix(const float teta);

	 EngineMath::mat4 RodriguezMatrix(const EngineMath::vec3 v3, const float teta);

	 EngineMath::mat4 ScaleMatrix(const  EngineMath::vec3 v3);

	 EngineMath::mat3 Mat4To3(const  EngineMath::mat4 m4);

	 EngineMath::mat4 Mat3To4(const  EngineMath::mat3 m4);

	 EngineMath::mat4 PerspectiveMatrix(float fov, float aspect, float near, float far);

	 EngineMath::mat4 OrthographicMatrix(float left, float right, float top, float bottom, float near, float MatrixFactory);

	 EngineMath::mat4 ViewMatrix(EngineMath::vec3 eye, EngineMath::vec3 center, EngineMath::vec3 up);
}

namespace Numbers {

	unsigned int giveId();
}

namespace Colors {
	EngineMath::vec4 hsv2rgb(float hue, float saturation, float value);
}


#endif