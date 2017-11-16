#ifndef __VEC_H__
#define __VEC_H__
#include "GL/glew.h"
#include <stdlib.h>
#include <iostream>
#include <algorithm>
namespace EngineMath{

	class vec2 {
		public:

			GLfloat x;
			GLfloat y;


			vec2(GLfloat e0, GLfloat e1);


			  const vec2& operator+() const;
			  vec2 operator-() const;
			  GLfloat operator[](int i) const;

			  vec2& operator+=(const vec2 &v2);
			  vec2& operator-=(const vec2 &v2);
			  vec2& operator*=(const vec2 &v2);
			  vec2& operator/=(const vec2 &v2);
			  vec2& operator*=(const GLfloat t);
			  vec2& operator/=(const GLfloat t);

			  GLfloat length() const;

			  GLfloat squared_length() const;

			  void normalize();		
	};

	  std::istream& operator>>(std::istream &is, vec2 &t);

	  std::ostream& operator<<(std::ostream &os, const vec2 &t);

	  vec2 operator+(const vec2 &v1, const vec2 &v2);

	  vec2 operator-(const vec2 &v1, const vec2 &v2);

	  vec2 operator*(const vec2 &v1, const vec2 &v2);

	  vec2 operator/(const vec2 &v1, const vec2 &v2);

	  vec2 operator*(const vec2 &v, GLfloat t);

	  vec2 operator*(GLfloat t, const vec2 &v);

	  vec2 operator/(const vec2 &v, GLfloat t);

	  GLfloat dot(const vec2 &v1, const vec2 &v2);

	  vec2 normalize(vec2 v);



	class vec3 {
		public:

			GLfloat x;
			GLfloat y;
			GLfloat z;


			vec3(GLfloat e0, GLfloat e1, GLfloat e2);

			vec3(vec2 vector2, GLfloat e2);

			vec3(GLfloat e0, vec2 vector2);


			const vec3& operator+() const;
			vec3 operator-() const;
			GLfloat operator[](int i) const;



			  vec3& operator+=(const vec3 &v2);
			  vec3& operator-=(const vec3 &v2);
			  vec3& operator*=(const vec3 &v2);
			  vec3& operator/=(const vec3 &v2);
			  vec3& operator*=(const GLfloat t);
			  vec3& operator/=(const GLfloat t);

			  GLfloat length() const;

			  GLfloat squared_length() const;

			  void normalize();		
	};

	std::istream& operator>>(std::istream &is, vec3 &t);

	std::ostream& operator<<(std::ostream &os, const vec3 &t);

	vec3 operator+(const vec3 &v1, const vec3 &v2);

	vec3 operator-(const vec3 &v1, const vec3 &v2);

	vec3 operator*(const vec3 &v1, const vec3 &v2);

	vec3 operator/(const vec3 &v1, const vec3 &v2);

	vec3 operator*(const vec3 &v, GLfloat t);

	vec3 operator*(GLfloat t, const vec3 &v);

	vec3 operator/(const vec3 &v, GLfloat t);

	GLfloat dot(const vec3 &v1, const vec3 &v2);

	vec3 cross(const vec3 &v1, const vec3 &v2);

	vec3 normalize(vec3 v);

	vec3 rodriguezFormula(vec3 v, vec3 around, GLfloat teta);

	vec3 clean(vec3 v, GLfloat eps);

	vec3 lerp(vec3 start, vec3 finish, float rate);

	class vec4 {
		public:

			GLfloat x;
			GLfloat y;
			GLfloat z;
			GLfloat w;

			vec4(){}

			vec4(GLfloat e0, GLfloat e1, GLfloat e2, GLfloat e3);

			vec4(vec3 vector3, GLfloat e3);

			vec4(GLfloat e0, vec3 vector3);

			vec4(vec2 v1, vec2 v2);

			vec4(vec2 vector2, GLfloat e2, GLfloat e3);

			vec4(GLfloat e0, GLfloat e1, vec2 vector2);

			vec4(GLfloat e0, vec2 vector2, GLfloat e3);

			const vec4& operator+() const;
			vec4 operator-() const;
			GLfloat operator[](int i) const;

			  vec4& operator+=(const vec4 &v2);
			  vec4& operator-=(const vec4 &v2);
			  vec4& operator*=(const vec4 &v2);
			  vec4& operator/=(const vec4 &v2);
			  vec4& operator*=(const GLfloat t);
			  vec4& operator/=(const GLfloat t);

			  GLfloat length() const;

			  GLfloat squared_length() const;

			  void normalize();		
	};

	std::istream& operator>>(std::istream &is, vec4 &t);

	std::ostream& operator<<(std::ostream &os, const vec4 &t);

	vec4 operator+(const vec4 &v1, const vec4 &v2);

	vec4 operator-(const vec4 &v1, const vec4 &v2);

	vec4 operator*(const vec4 &v1, const vec4 &v2);

	vec4 operator/(const vec4 &v1, const vec4 &v2);

	vec4 operator*(const vec4 &v, GLfloat t);

	vec4 operator*(GLfloat t, const vec4 &v);

	vec4 operator/(const vec4 &v, GLfloat t);

	GLfloat dot(const vec4 &v1, const vec4 &v2);

	vec4 normalize(vec4 v);

	const GLfloat * glFormat(vec4 v);
	
	class glVec4{
		public:
			GLfloat xyzw[4];
		
			glVec4(vec4 v);
	};
}

#endif
