#include "mat.h"

namespace EngineMath {

	mat2::mat2() {}

	mat2::mat2(GLfloat k) {
		for (int i = 0; i < 4; i++) {
			m[i] = k;
		}
	}

	mat2::mat2(GLfloat m11, GLfloat m12,
		GLfloat m21, GLfloat m22) {
		m[0] = m11;
		m[1] = m21;
		m[2] = m12;
		m[3] = m22;
	}

	const mat2 & mat2::operator+() const
	{
		return *this;
	}

	mat2 mat2::operator-() const
	{
		return mat2(-m[0], -m[2],
			-m[1], -m[3]);
	}

	mat2 & mat2::operator+=(const mat2 & m2)
	{
		for (int i=0; i < 4; i++) {
			m[i] += m2.m[i];
		}
		return *this;
	}

	mat2 & mat2::operator-=(const mat2 & m2)
	{
		for (int i=0; i < 4; i++) {
			m[i] -= m2.m[i];
		}
		return *this;
	}

	mat2 & mat2::operator*=(const mat2 & m2)
	{
		m[0] = m[0] * m2.m[0] + m[2] * m2.m[1];
		m[2] = m[0] * m2.m[2] + m[2] * m2.m[3];
		m[1] = m[1] * m2.m[0] + m[3] * m2.m[1];
		m[3] = m[1] * m2.m[2] + m[3] * m2.m[3];
		return *this;
	}

	mat2 & mat2::operator/=(const mat2 & m1)
	{
		mat2 m2 = inverse(m1);
		m[0] = m[0] * m2.m[0] + m[2] * m2.m[1];
		m[2] = m[0] * m2.m[2] + m[2] * m2.m[3];
		m[1] = m[1] * m2.m[0] + m[3] * m2.m[1];
		m[3] = m[1] * m2.m[2] + m[3] * m2.m[3];
		return *this;
	}

	mat2 & mat2::operator*=(const GLfloat t)
	{
		for (int i=0; i < 4; i++) {
			m[i] *= t;
		}
		return *this;
	}

	mat2 & mat2::operator/=(const GLfloat t)
	{
		for (int i=0; i < 4; i++) {
			m[i] /= t;
		}
		return *this;
	}

	vec2 mat2::operator[](int i) const
	{
		if (i == 0) {
			return vec2(m[0], m[2]);
		}
		else if (i == 1) {
			return vec2(m[1], m[3]);
		}
		else {
			std::cerr << "Index Error for Matrix 2*2 with value :\n" << *this << std::endl;
			return vec2(INFINITY, INFINITY);
		}
	}


	//-----------------------------------------------------------------------

	std::ostream & operator<<(std::ostream & os, const mat2 & m2)
	{
		os << "\n|" << m2.m[0] << "\t" << m2.m[2] << "|\n"
			<< "|" << m2.m[1] << "\t" << m2.m[3] << "| 2*2" << std::endl;
		return os;
	}

	GLfloat determinant(const mat2 m)
	{
		return m.m[0] * m.m[3] - m.m[2] * m.m[1];
	}

	mat2 inverse(const mat2 m)
	{
		if (determinant(m) != 0) {
			return mat2(m.m[3], -m.m[2], -m.m[1], m.m[0]) * (1 / determinant(m));
		}
		std::cerr << "Trying to compute Inverse of a Matrix with Determinant equal to Zero:" << m << std::endl;
		return mat2(INFINITY);
	}

	mat2 transpose(const mat2 m)
	{
		return mat2(m.m[0], m.m[1],
					m.m[2], m.m[3]);
	}

	mat2 operator+(const mat2 & m1, const mat2 & m2)
	{
		return mat2(m1.m[0] + m2.m[0], m1.m[2] + m2.m[2],
			m1.m[1] + m2.m[1], m1.m[3] + m2.m[3]);
	}

	mat2 operator-(const mat2 & m1, const mat2 & m2)
	{
		return mat2(m1.m[0] - m2.m[0], m1.m[2] - m2.m[2],
			m1.m[1] - m2.m[1], m1.m[3] - m2.m[3]);
	}

	mat2 operator*(const mat2 & m1, const mat2 & m2)
	{
		return mat2(m1.m[0] * m2.m[0] + m1.m[2] * m2.m[1], m1.m[0] * m2.m[2] + m1.m[2] * m2.m[3],
			m1.m[1] * m2.m[0] + m1.m[3] * m2.m[1], m1.m[1] * m2.m[2] + m1.m[3] * m2.m[3]);
	}

	mat2 operator*(const mat2 & m, const GLfloat & f)
	{
		return mat2(m.m[0] * f, m.m[2] * f,
			m.m[1] * f, m.m[3] * f);
	}

	mat2 operator/(const mat2 & m1, const mat2 & m2)
	{
		return m1*inverse(m2);
	}

	mat2 operator/(const mat2 & m, const GLfloat & f)
	{
		return mat2(m.m[0] / f, m.m[2] / f,
			m.m[1] / f, m.m[3] / f);
	}

	vec2 operator*(const mat2 & m, const vec2 & v)
	{
		return vec2(m.m[0]*v.x + m.m[2] * v.y, m.m[1]*v.x + m.m[3]*v.x);
	}


	//----------------------------------------------------------------------------------

	mat3::mat3() {/**/}

	mat3::mat3(GLfloat k)
	{
		for (int i = 0; i < 9; i++) {
			m[i] = k;
		}
	}

	mat3::mat3(GLfloat m11, GLfloat m12, GLfloat m13,
		GLfloat m21, GLfloat m22, GLfloat m23,
		GLfloat m31, GLfloat m32, GLfloat m33)
	{

		m[0] = m11;
		m[1] = m21;
		m[2] = m31;
		m[3] = m12;
		m[4] = m22;
		m[5] = m32;
		m[6] = m13;
		m[7] = m23;
		m[8] = m33;
	}

	const mat3 & mat3::operator+() const
	{
		return *this;
	}

	mat3 mat3::operator-() const
	{
		return mat3(-m[0], -m[3], -m[6],
			-m[1], -m[4], -m[7],
			-m[2], -m[5], -m[8]);
	}

	mat3 & mat3::operator+=(const mat3 & m3)
	{
		for (int i=0; i < 9; i++) {
			m[i] += m3.m[i];
		}
		return *this;
	}

	mat3 & mat3::operator-=(const mat3 & m3)
	{
		for (int i=0; i < 9; i++) {
			m[i] -= m3.m[i];
		}
		return *this;
	}

	mat3 & mat3::operator*=(const mat3 & m3)
	{
		m[0] = m[0] * m3.m[0] + m[3] * m3.m[1] + m[6] * m3.m[2];
		m[1] = m[1] * m3.m[0] + m[4] * m3.m[1] + m[7] * m3.m[2];
		m[2] = m[2] * m3.m[0] + m[5] * m3.m[1] + m[8] * m3.m[2];

		m[3] = m[0] * m3.m[3] + m[3] * m3.m[4] + m[6] * m3.m[5];
		m[4] = m[1] * m3.m[3] + m[4] * m3.m[4] + m[7] * m3.m[5];
		m[5] = m[2] * m3.m[3] + m[5] * m3.m[4] + m[8] * m3.m[5];

		m[6] = m[0] * m3.m[6] + m[3] * m3.m[7] + m[6] * m3.m[8];
		m[7] = m[1] * m3.m[6] + m[4] * m3.m[7] + m[7] * m3.m[8];
		m[8] = m[2] * m3.m[6] + m[5] * m3.m[7] + m[8] * m3.m[8];

		return *this;
	}

	mat3 & mat3::operator/=(const mat3 & m1)
	{
		mat3 m3 = inverse(m1);
		m[0] = m[0] * m3.m[0] + m[3] * m3.m[1] + m[6] * m3.m[2];
		m[1] = m[1] * m3.m[0] + m[4] * m3.m[1] + m[7] * m3.m[2];
		m[2] = m[2] * m3.m[0] + m[5] * m3.m[1] + m[8] * m3.m[2];

		m[3] = m[0] * m3.m[3] + m[3] * m3.m[4] + m[6] * m3.m[5];
		m[4] = m[1] * m3.m[3] + m[4] * m3.m[4] + m[7] * m3.m[5];
		m[5] = m[2] * m3.m[3] + m[5] * m3.m[4] + m[8] * m3.m[5];

		m[6] = m[0] * m3.m[6] + m[3] * m3.m[7] + m[6] * m3.m[8];
		m[7] = m[1] * m3.m[6] + m[4] * m3.m[7] + m[7] * m3.m[8];
		m[8] = m[2] * m3.m[6] + m[5] * m3.m[7] + m[8] * m3.m[8];

		return *this;
	}

	mat3 & mat3::operator*=(const GLfloat t)
	{
		for (int i=0; i < 9; i++) {
			m[i] *= t;
		}
		return *this;
	}

	mat3 & mat3::operator/=(const GLfloat t)
	{
		for (int i=0; i < 9; i++) {
			m[i] /= t;
		}
		return *this;
	}

	vec3 mat3::operator[](int i) const
	{
		if (i == 0) {
			return vec3(m[0], m[3], m[6]);
		}
		else if (i == 1) {
			return vec3(m[1], m[4], m[7]);
		}
		else if (i == 2) {
			return vec3(m[2], m[5], m[8]);
		}
		else {
			std::cerr << "Index Error for Matrix 3*3 with value :" << *this << std::endl;
			return vec3(INFINITY, INFINITY, INFINITY);
		}
	}

	std::ostream & operator<<(std::ostream & os, const mat3 & m3)
	{
		os << "\n|" << m3.m[0] << "\t" << m3.m[3] << "\t" << m3.m[6] << "|\n"
			 << "|" << m3.m[1] << "\t" << m3.m[4] << "\t" << m3.m[7] << "|\n"
			 << "|" << m3.m[2] << "\t" << m3.m[5] << "\t" << m3.m[8] << "| 3*3" << std::endl;
		return os;
	}

	GLfloat determinant(const mat3 m)
	{
		return m.m[0] * m.m[4] * m.m[8]
			+ m.m[3] * m.m[7] * m.m[2]
			+ m.m[6] * m.m[1] * m.m[5]
			- m.m[0] * m.m[7] * m.m[5]
			- m.m[3] * m.m[1] * m.m[8]
			- m.m[6] * m.m[4] * m.m[2];
	}

	mat3 transpose(const mat3 m)
	{
		return mat3(m.m[0],m.m[1],m.m[2],
					m.m[3],m.m[4],m.m[5],
					m.m[6],m.m[7],m.m[8]);
	}

	mat3 inverse(const mat3 m)
	{
		GLfloat det = determinant(m);
		if (det != 0.0f)
			return mat3(m.m[4] * m.m[8] - m.m[7] * m.m[5], m.m[6] * m.m[5] - m.m[3] * m.m[8], m.m[3] * m.m[7] - m.m[6] * m.m[4],
				m.m[7] * m.m[2] - m.m[1] * m.m[8], m.m[0] * m.m[8] - m.m[6] * m.m[2], m.m[6] * m.m[1] - m.m[0] * m.m[7],
				m.m[1] * m.m[5] - m.m[4] * m.m[2], m.m[3] * m.m[2] - m.m[0] * m.m[5], m.m[0] * m.m[4] - m.m[3] * m.m[1])*(1 / det);
		std::cerr << "Trying to invert 3*3 matrix with determinant == 0:" << m << std::endl;
		return mat3(INFINITY);
	}

	mat3 operator+(const mat3 & m1, const mat3 & m2)
	{
		return mat3(m1.m[0] + m2.m[0], m1.m[3] + m2.m[3], m1.m[6] + m2.m[6],
			m1.m[1] + m2.m[1], m1.m[4] + m2.m[4], m1.m[7] + m2.m[7],
			m1.m[2] + m2.m[2], m1.m[5] + m2.m[5], m1.m[8] + m2.m[8]);
	}

	mat3 operator-(const mat3 & m1, const mat3 & m2)
	{
		return mat3(m1.m[0] - m2.m[0], m1.m[3] - m2.m[3], m1.m[6] - m2.m[6],
			m1.m[1] - m2.m[1], m1.m[4] - m2.m[4], m1.m[7] - m2.m[7],
			m1.m[2] - m2.m[2], m1.m[5] - m2.m[5], m1.m[8] - m2.m[8]);
	}

	mat3 operator*(const mat3 & m, const GLfloat & f)
	{
		return mat3(m.m[0] * f, m.m[3] * f, m.m[6] * f,
					m.m[1] * f, m.m[4] * f, m.m[7] * f,
					m.m[2] * f, m.m[5] * f, m.m[8] * f);
	}

	mat3 operator*(const mat3 & m1, const mat3 & m2)
	{
		return mat3(m1.m[0] * m2.m[0] + m1.m[3] * m2.m[1] + m1.m[6] * m2.m[2], m1.m[0] * m2.m[3] + m1.m[3] * m2.m[4] + m1.m[6] * m2.m[5], m1.m[0] * m2.m[6] + m1.m[3] * m2.m[7] + m1.m[6] * m2.m[8],
			m1.m[1] * m2.m[0] + m1.m[4] * m2.m[1] + m1.m[7] * m2.m[2], m1.m[1] * m2.m[3] + m1.m[4] * m2.m[4] + m1.m[7] * m2.m[5], m1.m[1] * m2.m[6] + m1.m[4] * m2.m[7] + m1.m[7] * m2.m[8],
			m1.m[2] * m2.m[0] + m1.m[5] * m2.m[1] + m1.m[8] * m2.m[2], m1.m[2] * m2.m[3] + m1.m[5] * m2.m[4] + m1.m[8] * m2.m[5], m1.m[2] * m2.m[6] + m1.m[5] * m2.m[7] + m1.m[8] * m2.m[8]);
	}

	mat3 operator/(const mat3 & m1, const mat3 & m2)
	{
		return m1*inverse(m2);
	}

	mat3 operator/(const mat3 & m, const GLfloat & f)
	{
		return mat3(m.m[0] / f, m.m[3] / f, m.m[6] / f,
			m.m[1] / f, m.m[4] / f, m.m[7] / f,
			m.m[2] / f, m.m[5] / f, m.m[8] / f);
	}

	vec3 operator*(const mat3 & m, const vec3 & v)
	{
		return vec3(m.m[0]*v.x + m.m[3] * v.y + m.m[6]*v.z,
					m.m[1]*v.x + m.m[4] * v.y + m.m[7]*v.z,
					m.m[2]*v.x + m.m[5] * v.y + m.m[8]*v.z);
	}


	//-------------------------------------------------------------------------------

	mat4::mat4() {}

	mat4::mat4(GLfloat k)
	{
		for (int i = 0; i < 16; i++) {
			m[i] = k;
		}
	}

	mat4::mat4(GLfloat m11, GLfloat m12, GLfloat m13, GLfloat m14,
		GLfloat m21, GLfloat m22, GLfloat m23, GLfloat m24,
		GLfloat m31, GLfloat m32, GLfloat m33, GLfloat m34,
		GLfloat m41, GLfloat m42, GLfloat m43, GLfloat m44)
	{

		m[0] = m11;
		m[1] = m21;
		m[2] = m31;
		m[3] = m41;
		m[4] = m12;
		m[5] = m22;
		m[6] = m32;
		m[7] = m42;
		m[8] = m13;
		m[9] = m23;
		m[10] = m33;
		m[11] = m43;
		m[12] = m14;
		m[13] = m24;
		m[14] = m34;
		m[15] = m44;

	}

	const mat4 & mat4::operator+() const { return *this; }

	mat4 mat4::operator-() const
	{
		return mat4(-m[0], -m[4], -m[8], -m[12],
					-m[1], -m[5], -m[9], -m[13],
					-m[2], -m[6], -m[10], -m[14],
					-m[3], -m[7], -m[11], -m[15]);
	}

	vec4 mat4::operator[](int i) const
	{
		if (i == 0) {
			return vec4(m[0], m[4], m[8], m[12]);
		}
		else if (i == 1) {
			return vec4(m[1], m[5], m[9], m[13]);
		}
		else if (i == 2) {
			return vec4(m[2], m[6], m[10], m[14]);
		}
		else if (i == 3) {
			return vec4(m[3], m[7], m[11], m[15]);
		}
		else {
			std::cerr << "Index Error for Matrix 3*3 with value :" << *this << std::endl;
			return vec4(INFINITY, INFINITY, INFINITY, INFINITY);
		}
	}

	mat4 & mat4::operator+=(const mat4 & m4)
	{
		for (int i=0; i < 16; i++) {
			m[i] += m4.m[i];
		}
		return *this;
	}

	mat4 & mat4::operator-=(const mat4 & m4)
	{
		for (int i=0; i < 16; i++) {
			m[i] -= m4.m[i];
		}
		return *this;
	}
	
	mat4 & mat4::operator*=(const mat4 & m4)
	{
		m[0] = m[0] * m4.m[0] + m[4] * m4.m[1] + m[8] * m4.m[2] + m[12] * m4.m[3];
		m[4] = m[0] * m4.m[4] + m[4] * m4.m[5] + m[8] * m4.m[6] + m[12] * m4.m[7];
		m[8] = m[0] * m4.m[8] + m[4] * m4.m[9] + m[8] * m4.m[10] + m[12] * m4.m[11];
		m[12] = m[0] * m4.m[12] + m[4] * m4.m[13] + m[8] * m4.m[14] + m[12] * m4.m[15];

		m[1] = m[1] * m4.m[0] + m[5] * m4.m[1] + m[9] * m4.m[2] + m[13] * m4.m[3];
		m[5] = m[1] * m4.m[4] + m[5] * m4.m[5] + m[9] * m4.m[6] + m[13] * m4.m[7];
		m[9] = m[1] * m4.m[8] + m[5] * m4.m[9] + m[9] * m4.m[10] + m[13] * m4.m[11];
		m[13] = m[1] * m4.m[12] + m[5] * m4.m[13] + m[9] * m4.m[14] + m[13] * m4.m[15];
		
		m[2] = m[2] * m4.m[0] + m[6] * m4.m[1] + m[10] * m4.m[2] + m[14] * m4.m[3];
		m[6] = m[2] * m4.m[4] + m[6] * m4.m[5] + m[10] * m4.m[6] + m[14] * m4.m[7];
		m[10] = m[2] * m4.m[8] + m[6] * m4.m[9] + m[10] * m4.m[10] + m[14] * m4.m[11];
		m[14] = m[2] * m4.m[12] + m[6] * m4.m[13] + m[10] * m4.m[14] + m[14] * m4.m[15];
		
		m[3] = m[3] * m4.m[0] + m[7] * m4.m[1] + m[11] * m4.m[2] + m[15] * m4.m[3];
		m[7] = m[3] * m4.m[4] + m[7] * m4.m[5] + m[11] * m4.m[6] + m[15] * m4.m[7];
		m[11] = m[3] * m4.m[8] + m[7] * m4.m[9] + m[11] * m4.m[10] + m[15] * m4.m[11];
		m[15] = m[3] * m4.m[12] + m[7] * m4.m[13] + m[11] * m4.m[14] + m[15] * m4.m[15];

		return *this;
	}

	mat4 & mat4::operator/=(const mat4 & m)
	{
		mat4 m4 = inverse(m);
		m[0] = m[0] * m4.m[0] + m[4] * m4.m[1] + m[8] * m4.m[2] + m[12] * m4.m[3];
		m[4] = m[0] * m4.m[4] + m[4] * m4.m[5] + m[8] * m4.m[6] + m[12] * m4.m[7];
		m[8] = m[0] * m4.m[8] + m[4] * m4.m[9] + m[8] * m4.m[10] + m[12] * m4.m[11];
		m[12] = m[0] * m4.m[12] + m[4] * m4.m[13] + m[8] * m4.m[14] + m[12] * m4.m[15];

		m[1] = m[1] * m4.m[0] + m[5] * m4.m[1] + m[9] * m4.m[2] + m[13] * m4.m[3];
		m[5] = m[1] * m4.m[4] + m[5] * m4.m[5] + m[9] * m4.m[6] + m[13] * m4.m[7];
		m[9] = m[1] * m4.m[8] + m[5] * m4.m[9] + m[9] * m4.m[10] + m[13] * m4.m[11];
		m[13] = m[1] * m4.m[12] + m[5] * m4.m[13] + m[9] * m4.m[14] + m[13] * m4.m[15];

		m[2] = m[2] * m4.m[0] + m[6] * m4.m[1] + m[10] * m4.m[2] + m[14] * m4.m[3];
		m[6] = m[2] * m4.m[4] + m[6] * m4.m[5] + m[10] * m4.m[6] + m[14] * m4.m[7];
		m[10] = m[2] * m4.m[8] + m[6] * m4.m[9] + m[10] * m4.m[10] + m[14] * m4.m[11];
		m[14] = m[2] * m4.m[12] + m[6] * m4.m[13] + m[10] * m4.m[14] + m[14] * m4.m[15];

		m[3] = m[3] * m4.m[0] + m[7] * m4.m[1] + m[11] * m4.m[2] + m[15] * m4.m[3];
		m[7] = m[3] * m4.m[4] + m[7] * m4.m[5] + m[11] * m4.m[6] + m[15] * m4.m[7];
		m[11] = m[3] * m4.m[8] + m[7] * m4.m[9] + m[11] * m4.m[10] + m[15] * m4.m[11];
		m[15] = m[3] * m4.m[12] + m[7] * m4.m[13] + m[11] * m4.m[14] + m[15] * m4.m[15];

		return *this;
	}

	mat4 & mat4::operator*=(const GLfloat t)
	{
		for (int i=0; i < 16; i++) {
			m[i] *= t;
		}
		return *this;
	}

	mat4 & mat4::operator/=(const GLfloat t)
	{
		for (int i=0; i < 16; i++) {
			m[i] /= t;
		}
		return *this;
	}

	std::ostream & operator<<(std::ostream & os, const mat4 & t)
	{
		os << "\n|" << t.m[0] << "\t" << t.m[4] << "\t" << t.m[8]  << "\t" << t.m[12] << "|\n"
			 << "|" << t.m[1] << "\t" << t.m[5] << "\t" << t.m[9]  << "\t" << t.m[13] << "|\n"
			 << "|" << t.m[2] << "\t" << t.m[6] << "\t" << t.m[10] << "\t" << t.m[14] << "|\n"
			 << "|" << t.m[3] << "\t" << t.m[7] << "\t" << t.m[11] << "\t" << t.m[15] << "|4x4" << std::endl;

		return os;
	}

	GLfloat determinant(const mat4 m)
	{
		mat4 m2 = transpose(m);
		return  m2.m[12] * m2.m[9] * m2.m[6] * m2.m[3] - m2.m[8] * m2.m[13] * m2.m[6] * m2.m[3] -
				m2.m[12] * m2.m[5] * m2.m[10] * m2.m[3] + m2.m[4] * m2.m[13] * m2.m[10] * m2.m[3] +
				m2.m[8] * m2.m[5] * m2.m[14] * m2.m[3] - m2.m[4] * m2.m[9] * m2.m[14] * m2.m[3] -
				m2.m[12] * m2.m[9] * m2.m[2] * m2.m[7] + m2.m[8] * m2.m[13] * m2.m[2] * m2.m[7] +
				m2.m[12] * m2.m[1] * m2.m[10] * m2.m[7] - m2.m[0] * m2.m[13] * m2.m[10] * m2.m[7] -
				m2.m[8] * m2.m[1] * m2.m[14] * m2.m[7] + m2.m[0] * m2.m[9] * m2.m[14] * m2.m[7] +
				m2.m[12] * m2.m[5] * m2.m[2] * m2.m[11] - m2.m[4] * m2.m[13] * m2.m[2] * m2.m[11] -
				m2.m[12] * m2.m[1] * m2.m[6] * m2.m[11] + m2.m[0] * m2.m[13] * m2.m[6] * m2.m[11] +
				m2.m[4] * m2.m[1] * m2.m[14] * m2.m[11] - m2.m[0] * m2.m[5] * m2.m[14] * m2.m[11] -
				m2.m[8] * m2.m[5] * m2.m[2] * m2.m[15] + m2.m[4] * m2.m[9] * m2.m[2] * m2.m[15] +
				m2.m[8] * m2.m[1] * m2.m[6] * m2.m[15] - m2.m[0] * m2.m[9] * m2.m[6] * m2.m[15] -
				m2.m[4] * m2.m[1] * m2.m[10] * m2.m[15] + m2.m[0] * m2.m[5] * m2.m[10] * m2.m[15];
	}

	mat4 transpose(const mat4 m)
	{
		return mat4(m.m[0], m.m[1], m.m[2], m.m[3], 
					m.m[4], m.m[5], m.m[6], m.m[7], 
					m.m[8], m.m[9], m.m[10], m.m[11], 
					m.m[12], m.m[13], m.m[14], m.m[15]);
	}

	mat4 inverse(const mat4 m)
	{
		GLfloat inv[16];
		mat4 m1 = m;

		inv[0] = m1.m[5] * m1.m[10] * m1.m[15] -
			m1.m[5] * m1.m[11] * m1.m[14] -
			m1.m[9] * m1.m[6] * m1.m[15] +
			m1.m[9] * m1.m[7] * m1.m[14] +
			m1.m[13] * m1.m[6] * m1.m[11] -
			m1.m[13] * m1.m[7] * m1.m[10];

		inv[4] = -m1.m[4] * m1.m[10] * m1.m[15] +
			m1.m[4] * m1.m[11] * m1.m[14] +
			m1.m[8] * m1.m[6] * m1.m[15] -
			m1.m[8] * m1.m[7] * m1.m[14] -
			m1.m[12] * m1.m[6] * m1.m[11] +
			m1.m[12] * m1.m[7] * m1.m[10];

		inv[8] = m1.m[4] * m1.m[9] * m1.m[15] -
			m1.m[4] * m1.m[11] * m1.m[13] -
			m1.m[8] * m1.m[5] * m1.m[15] +
			m1.m[8] * m1.m[7] * m1.m[13] +
			m1.m[12] * m1.m[5] * m1.m[11] -
			m1.m[12] * m1.m[7] * m1.m[9];

		inv[12] = -m1.m[4] * m1.m[9] * m1.m[14] +
			m1.m[4] * m1.m[10] * m1.m[13] +
			m1.m[8] * m1.m[5] * m1.m[14] -
			m1.m[8] * m1.m[6] * m1.m[13] -
			m1.m[12] * m1.m[5] * m1.m[10] +
			m1.m[12] * m1.m[6] * m1.m[9];

		inv[1] = -m1.m[1] * m1.m[10] * m1.m[15] +
			m1.m[1] * m1.m[11] * m1.m[14] +
			m1.m[9] * m1.m[2] * m1.m[15] -
			m1.m[9] * m1.m[3] * m1.m[14] -
			m1.m[13] * m1.m[2] * m1.m[11] +
			m1.m[13] * m1.m[3] * m1.m[10];

		inv[5] = m1.m[0] * m1.m[10] * m1.m[15] -
			m1.m[0] * m1.m[11] * m1.m[14] -
			m1.m[8] * m1.m[2] * m1.m[15] +
			m1.m[8] * m1.m[3] * m1.m[14] +
			m1.m[12] * m1.m[2] * m1.m[11] -
			m1.m[12] * m1.m[3] * m1.m[10];

		inv[9] = -m1.m[0] * m1.m[9] * m1.m[15] +
			m1.m[0] * m1.m[11] * m1.m[13] +
			m1.m[8] * m1.m[1] * m1.m[15] -
			m1.m[8] * m1.m[3] * m1.m[13] -
			m1.m[12] * m1.m[1] * m1.m[11] +
			m1.m[12] * m1.m[3] * m1.m[9];

		inv[13] = m1.m[0] * m1.m[9] * m1.m[14] -
			m1.m[0] * m1.m[10] * m1.m[13] -
			m1.m[8] * m1.m[1] * m1.m[14] +
			m1.m[8] * m1.m[2] * m1.m[13] +
			m1.m[12] * m1.m[1] * m1.m[10] -
			m1.m[12] * m1.m[2] * m1.m[9];

		inv[2] = m1.m[1] * m1.m[6] * m1.m[15] -
			m1.m[1] * m1.m[7] * m1.m[14] -
			m1.m[5] * m1.m[2] * m1.m[15] +
			m1.m[5] * m1.m[3] * m1.m[14] +
			m1.m[13] * m1.m[2] * m1.m[7] -
			m1.m[13] * m1.m[3] * m1.m[6];

		inv[6] = -m1.m[0] * m1.m[6] * m1.m[15] +
			m1.m[0] * m1.m[7] * m1.m[14] +
			m1.m[4] * m1.m[2] * m1.m[15] -
			m1.m[4] * m1.m[3] * m1.m[14] -
			m1.m[12] * m1.m[2] * m1.m[7] +
			m1.m[12] * m1.m[3] * m1.m[6];

		inv[10] = m1.m[0] * m1.m[5] * m1.m[15] -
			m1.m[0] * m1.m[7] * m1.m[13] -
			m1.m[4] * m1.m[1] * m1.m[15] +
			m1.m[4] * m1.m[3] * m1.m[13] +
			m1.m[12] * m1.m[1] * m1.m[7] -
			m1.m[12] * m1.m[3] * m1.m[5];

		inv[14] = -m1.m[0] * m1.m[5] * m1.m[14] +
			m1.m[0] * m1.m[6] * m1.m[13] +
			m1.m[4] * m1.m[1] * m1.m[14] -
			m1.m[4] * m1.m[2] * m1.m[13] -
			m1.m[12] * m1.m[1] * m1.m[6] +
			m1.m[12] * m1.m[2] * m1.m[5];

		inv[3] = -m1.m[1] * m1.m[6] * m1.m[11] +
			m1.m[1] * m1.m[7] * m1.m[10] +
			m1.m[5] * m1.m[2] * m1.m[11] -
			m1.m[5] * m1.m[3] * m1.m[10] -
			m1.m[9] * m1.m[2] * m1.m[7] +
			m1.m[9] * m1.m[3] * m1.m[6];

		inv[7] = m1.m[0] * m1.m[6] * m1.m[11] -
			m1.m[0] * m1.m[7] * m1.m[10] -
			m1.m[4] * m1.m[2] * m1.m[11] +
			m1.m[4] * m1.m[3] * m1.m[10] +
			m1.m[8] * m1.m[2] * m1.m[7] -
			m1.m[8] * m1.m[3] * m1.m[6];

		inv[11] = -m1.m[0] * m1.m[5] * m1.m[11] +
			m1.m[0] * m1.m[7] * m1.m[9] +
			m1.m[4] * m1.m[1] * m1.m[11] -
			m1.m[4] * m1.m[3] * m1.m[9] -
			m1.m[8] * m1.m[1] * m1.m[7] +
			m1.m[8] * m1.m[3] * m1.m[5];

		inv[15] = m1.m[0] * m1.m[5] * m1.m[10] -
			m1.m[0] * m1.m[6] * m1.m[9] -
			m1.m[4] * m1.m[1] * m1.m[10] +
			m1.m[4] * m1.m[2] * m1.m[9] +
			m1.m[8] * m1.m[1] * m1.m[6] -
			m1.m[8] * m1.m[2] * m1.m[5];

		return mat4(inv[0], inv[1], inv[2], inv[3],
					inv[4], inv[5], inv[6], inv[7],
					inv[8], inv[9], inv[10], inv[11],
					inv[12], inv[13], inv[14], inv[15])*(1/determinant(m));
	}

	mat4 operator*(const mat4 & m, const GLfloat & f)
	{
		return mat4(m.m[0]*f, m.m[1]*f, m.m[2]*f, m.m[3]*f,
					m.m[4]*f, m.m[5]*f, m.m[6]*f, m.m[7]*f,
					m.m[8]*f, m.m[9]*f, m.m[10]*f, m.m[11]*f,
					m.m[12]*f, m.m[13]*f, m.m[14]*f, m.m[15]*f);
	}

	mat4 operator+(const mat4 & m1, const mat4 & m2)
	{
		return mat4(m1.m[0] + m2.m[0], m1.m[1] + m2.m[1], m1.m[2] + m2.m[2], m1.m[3] + m2.m[3],
					m1.m[4] + m2.m[4], m1.m[5] + m2.m[5], m1.m[6] + m2.m[6], m1.m[7] + m2.m[7],
					m1.m[8] + m2.m[8], m1.m[9] + m2.m[9], m1.m[10] + m2.m[10], m1.m[11] + m2.m[11],
					m1.m[12] + m2.m[12], m1.m[13] + m2.m[13], m1.m[14] + m2.m[14], m1.m[15] + m2.m[15]);
	}

	mat4 operator-(const mat4 & m1, const mat4 & m2)
	{
		return mat4(m1.m[0] - m2.m[0], m1.m[1] - m2.m[1], m1.m[2] - m2.m[2], m1.m[3] - m2.m[3],
			m1.m[4] - m2.m[4], m1.m[5] - m2.m[5], m1.m[6] - m2.m[6], m1.m[7] - m2.m[7],
			m1.m[8] - m2.m[8], m1.m[9] - m2.m[9], m1.m[10] - m2.m[10], m1.m[11] - m2.m[11],
			m1.m[12] - m2.m[12], m1.m[13] - m2.m[13], m1.m[14] - m2.m[14], m1.m[15] - m2.m[15]);
	}

	mat4 operator/(const mat4 & m, const GLfloat & f)
	{
		return m*(1/f);
	}

	vec4 operator*(const mat4 & m, const vec4 & v)
	{
		return vec4(m.m[0] * v.x + m.m[4] * v.y + m.m[8]  * v.z + m.m[12] * v.w,
					m.m[1] * v.x + m.m[5] * v.y + m.m[9]  * v.z + m.m[13] * v.w,
					m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14] * v.w,
					m.m[3] * v.x + m.m[7] * v.y + m.m[11] * v.z + m.m[15] * v.w	);
	}

	mat4 clean(const mat4 & m)
	{
		mat4 aux = m;
		for (int i = 0; i < 16; i++) {
			if (abs(m.m[i]) < 0.0001f) {
				aux.m[i] = 0;
			}
		}
		return aux;
	}



	mat4 operator*(const mat4 & m1, const mat4 & m2)
	{
		return mat4(m1.m[0] * m2.m[0] + m1.m[4] * m2.m[1] + m1.m[8] * m2.m[2] + m1.m[12]  * m2.m[3], m1.m[0] * m2.m[4] + m1.m[4] * m2.m[5] + m1.m[8] * m2.m[6] + m1.m[12]  * m2.m[7], m1.m[0] * m2.m[8] + m1.m[4] * m2.m[9] + m1.m[8]  * m2.m[10] + m1.m[12] * m2.m[11], m1.m[0] * m2.m[12] + m1.m[4] * m2.m[13] + m1.m[8]  * m2.m[14] + m1.m[12] * m2.m[15],
					m1.m[1] * m2.m[0] + m1.m[5] * m2.m[1] + m1.m[9] * m2.m[2] + m1.m[13]  * m2.m[3], m1.m[1] * m2.m[4] + m1.m[5] * m2.m[5] + m1.m[9] * m2.m[6] + m1.m[13]  * m2.m[7], m1.m[1] * m2.m[8] + m1.m[5] * m2.m[9] + m1.m[9]  * m2.m[10] + m1.m[13] * m2.m[11], m1.m[1] * m2.m[12] + m1.m[5] * m2.m[13] + m1.m[9]  * m2.m[14] + m1.m[13] * m2.m[15],
					m1.m[2] * m2.m[0] + m1.m[6] * m2.m[1] + m1.m[10] * m2.m[2] + m1.m[14] * m2.m[3], m1.m[2] * m2.m[4] + m1.m[6] * m2.m[5] + m1.m[10] * m2.m[6] + m1.m[14] * m2.m[7], m1.m[2] * m2.m[8] + m1.m[6] * m2.m[9] + m1.m[10] * m2.m[10] + m1.m[14] * m2.m[11], m1.m[2] * m2.m[12] + m1.m[6] * m2.m[13] + m1.m[10] * m2.m[14] + m1.m[14] * m2.m[15],
					m1.m[3] * m2.m[0] + m1.m[7] * m2.m[1] + m1.m[11] * m2.m[2] + m1.m[15] * m2.m[3], m1.m[3] * m2.m[4] + m1.m[7] * m2.m[5] + m1.m[11] * m2.m[6] + m1.m[15] * m2.m[7], m1.m[3] * m2.m[8] + m1.m[7] * m2.m[9] + m1.m[11] * m2.m[10] + m1.m[15] * m2.m[11], m1.m[3] * m2.m[12] + m1.m[7] * m2.m[13] + m1.m[11] * m2.m[14] + m1.m[15] * m2.m[15]);
	}

	mat4 operator/(const mat4 & m1, const mat4 & m2)
	{
		return m1*inverse(m2);
	}


}
