#ifndef __MAT_H__
#define __MAT_H__
#ifndef __VEC_H__
	#include "vec.h"
#endif
#include <stdlib.h>
#include <iostream>
#include "GL/glew.h"

namespace EngineMath{


	class mat2{
		
		public:
			GLfloat m[4];

			mat2();

			mat2(GLfloat k);

			mat2(GLfloat m11, GLfloat m12,
				 GLfloat m21, GLfloat m22);

			 const mat2& operator+() const;
			 mat2 operator-() const;

			 mat2& operator+=(const mat2 &m2);
			 mat2& operator-=(const mat2 &m2);
			 mat2& operator*=(const mat2 &m2);
			 mat2& operator/=(const mat2 &m2);
			 mat2& operator*=(const GLfloat t);
			 mat2& operator/=(const GLfloat t);
			 
			 vec2 operator[](int i) const;
	};


	std::ostream& operator<<(std::ostream &os, const mat2 &t);

	GLfloat determinant(const mat2 m);
	mat2 inverse(const mat2 m);
	mat2 transpose(const mat2 m);
	mat2 operator+(const mat2 &m1, const mat2 &m2);
	mat2 operator-(const mat2 &m1, const mat2 &m2);
	mat2 operator*(const mat2 &m1, const mat2 &m2);
	mat2 operator*(const mat2 &m, const GLfloat &f);
	mat2 operator/(const mat2 &m1, const mat2 &m2);
	mat2 operator/(const mat2 &m, const GLfloat &f);
	vec2 operator*(const mat2 & m, const vec2 & v);

//--------------------------------------------
	class mat3{
		
		public:
			GLfloat m[9];

			mat3();

			mat3(GLfloat k);

			mat3(GLfloat m11, GLfloat m12, GLfloat m13,
				GLfloat m21, GLfloat m22, GLfloat m23,
				GLfloat m31, GLfloat m32, GLfloat m33);

			 const mat3& operator+() const;
			 mat3 operator-() const;
			 mat3& operator+=(const mat3 &m3);
			 mat3& operator-=(const mat3 &m3);
			 mat3& operator*=(const mat3 &m3);
			 mat3& operator/=(const mat3 &m3);
			 mat3& operator*=(const GLfloat t);
			 mat3& operator/=(const GLfloat t);

			 vec3 operator[](int i) const;

	};


	std::ostream& operator<<(std::ostream &os, const mat3 &m);


	GLfloat determinant(const mat3 m);
	mat3 transpose(const mat3 m);

	mat3 inverse(const mat3 m);
	mat3 operator+(const mat3 &m1, const mat3 &m2);
	mat3 operator-(const mat3 &m1, const mat3 &m2);
	mat3 operator*(const mat3 &m, const GLfloat &f);
	mat3 operator*(const mat3 &m1, const mat3 &m2);
	mat3 operator/(const mat3 &m1, const mat3 &m2);
	mat3 operator/(const mat3 &m, const GLfloat &f);
	vec3 operator*(const mat3 &m, const vec3 &v);




//--------------------------------------------

	class mat4{
		
		public:
			GLfloat m[16];

			mat4();

			mat4(GLfloat k);

			mat4(GLfloat m11, GLfloat m12, GLfloat m13, GLfloat m14,
				GLfloat m21, GLfloat m22, GLfloat m23, GLfloat m24,
				GLfloat m31, GLfloat m32, GLfloat m33, GLfloat m34,
				GLfloat m41, GLfloat m42, GLfloat m43, GLfloat m44);

			const mat4& operator+() const;
			mat4 operator-() const;
			mat4& operator+=(const mat4 &m4);
			mat4& operator-=(const mat4 &m4);
			mat4& operator*=(const mat4 &m4);
			mat4& operator/=(const mat4 &m4);
			mat4& operator*=(const GLfloat t);
			mat4& operator/=(const GLfloat t);

			vec4 operator[](int i) const;
	};


	std::ostream& operator<<(std::ostream &os, const mat4 &t);
	
	GLfloat determinant(const mat4 m);
	
	mat4 transpose(const mat4 m);

	mat4 inverse(const mat4 m);
	
	mat4 operator*(const mat4 &m, const GLfloat &f);
	mat4 operator+(const mat4 &m1, const mat4 &m2);
	mat4 operator-(const mat4 &m1, const mat4 &m2);
	mat4 operator*(const mat4 &m1, const mat4 &m2);
	mat4 operator/(const mat4 &m1, const mat4 &m2);
	mat4 operator/(const mat4 &m, const GLfloat &f);
	vec4 operator*(const mat4 &m, const vec4 &v);

	mat4 clean(const mat4 &m);

}

#endif
