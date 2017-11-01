#ifndef __QUATERNIONS_H__
#define __QUATERNIONS_H__
#include "mat.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913

namespace EngineMath {

	const float qThreshold = (float)1.0e-5;

	class Quaternion	{
		public:
			float t, x, y, z;

		private:

		public:

			Quaternion();

			Quaternion(float teta, vec4 axis);

			~Quaternion();


			void clean();

			const float quadrance();

			const float norm();

			void normalize();

			Quaternion conjugate();

			Quaternion inverse();

			const vec4 getAngleAxis();

			mat4 getMat();
	};

	const Quaternion normalize(Quaternion q);

	std::ostream& operator<<(std::ostream &os, const Quaternion &t);


	Quaternion operator*(const Quaternion &m, const GLfloat &f);
	Quaternion operator*(const Quaternion &q1, const Quaternion &q2);
	Quaternion operator+(const Quaternion &q0, const Quaternion &q1);
	const Quaternion qLerp(const Quaternion& q0, const Quaternion& q1, float k);
	const Quaternion qSlerp(const Quaternion& q0, const Quaternion& q1, float k);



}
#endif