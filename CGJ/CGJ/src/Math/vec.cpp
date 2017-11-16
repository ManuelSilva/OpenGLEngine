#include "vec.h"

namespace EngineMath {

	vec2::vec2(GLfloat e0, GLfloat e1)
	{
		x = e0;
		y = e1;
	}

	  const vec2 & vec2::operator+() const
	{
		return *this;
	}

	  vec2 vec2::operator-() const
	{
		return vec2(-x, -y);
	}

	  GLfloat vec2::operator[](int i) const
	{
		if (i == 0) { return x; }
		else if (i == 1) { return y; }
		std::cerr << "Error invalid index operation for vec2" << std::endl;
		return INFINITY;
	}

	  vec2 & vec2::operator+=(const vec2 & v2)
	{
		x += v2.x;
		y += v2.y;
		return *this;
	}

	  vec2 & vec2::operator-=(const vec2 & v2)
	{
		x -= v2.x;
		y -= v2.y;
		return *this;
	}

	  vec2 & vec2::operator*=(const vec2 & v2)
	{
		x *= v2.x;
		y *= v2.y;
		return *this;
	}

	  vec2 & vec2::operator/=(const vec2 & v2)
	{
		x /= v2.x;
		y /= v2.y;
		return *this;
	}

	 vec2 & vec2::operator*=(const GLfloat t)
	{
		x *= t;
		y *= t;
		return *this;
	}

	  vec2 & vec2::operator/=(const GLfloat t)
	{
		GLfloat k = 1.0f / t;
		x *= k;
		y *= k;
		return *this;
	}

	 GLfloat vec2::length() const
	{
		return sqrt(x*x + y*y);
	}

	 GLfloat vec2::squared_length() const
	{
		return x*x + y*y;
	}

	  void vec2::normalize()
	{
		GLfloat k = 1.0f / length();
		x *= k;
		y *= k;
	}

	std::istream & operator>>(std::istream & is, vec2 & t)
	{
		is >> t.x >> t.y;
		return is;
	}

	std::ostream & operator<<(std::ostream & os, const vec2 & t)
	{
		os << "vec2(" << t.x << "," << t.y << ") ";
		return os;
	}

	vec2 operator+(const vec2 & v1, const vec2 & v2)
	{
		return vec2(v1.x + v2.x, v1.y + v2.y);
	}

	vec2 operator-(const vec2 & v1, const vec2 & v2)
	{
		return vec2(v1.x - v2.x, v1.y - v2.y);
	}

	vec2 operator*(const vec2 & v1, const vec2 & v2)
	{
		return vec2(v1.x * v2.x, v1.y * v2.y);
	}

	vec2 operator/(const vec2 & v1, const vec2 & v2)
	{
		return vec2(v1.x / v2.x, v1.y / v2.y);
	}

	vec2 operator*(const vec2 & v, GLfloat t)
	{
		return vec2(v.x * t, v.y * t);
	}

	vec2 operator*(GLfloat t, const vec2 & v)
	{
		return vec2(v.x * t, v.y * t);
	}

	vec2 operator/(const vec2 & v, GLfloat t)
	{
		return vec2(v.x / t, v.y / t);
	}

	GLfloat dot(const vec2 & v1, const vec2 & v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	vec2 normalize(vec2 v)
	{
		return v / v.length();
	}


	//---------------------------------------------------------------

	vec3::vec3(GLfloat e0, GLfloat e1, GLfloat e2)
	{
		x = e0;
		y = e1;
		z = e2;
	}

	vec3::vec3(vec2 vector2, GLfloat e2)
	{
		x = vector2.x;
		y = vector2.y;
		z = e2;
	}

	vec3::vec3(GLfloat e0, vec2 vector2)
	{
		x = e0;
		y = vector2.x;
		z = vector2.y;
	}

	const vec3 & vec3::operator+() const
	{
		return *this;
	}

	vec3 vec3::operator-() const
	{
		return vec3(-x, -y, -z);
	}

	GLfloat vec3::operator[](int i) const
	{
		if (i == 0) { return x; }
		else if (i == 1) { return y; }
		else if (i == 2) { return z; }
		std::cerr << "Error invalid index operation for vec3" << std::endl;
		return INFINITY;
	}

	vec3 & vec3::operator+=(const vec3 & v2)
	{
		x += v2.x;
		y += v2.y;
		z += v2.z;
		return *this;
	}

	vec3 & vec3::operator-=(const vec3 & v2)
	{
		x -= v2.x;
		y -= v2.y;
		z -= v2.z;
		return *this;
	}

	vec3 & vec3::operator*=(const vec3 & v2)
	{
		x *= v2.x;
		y *= v2.y;
		z *= v2.z;
		return *this;
	}

	vec3 & vec3::operator/=(const vec3 & v2)
	{
		x /= v2.x;
		y /= v2.y;
		z /= v2.z;
		return *this;
	}

	vec3 & vec3::operator*=(const GLfloat t)
	{
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	vec3 & vec3::operator/=(const GLfloat t)
	{
		GLfloat k = 1.0f / t;
		x *= k;
		y *= k;
		z *= k;
		return *this;
	}

	GLfloat vec3::length() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	GLfloat vec3::squared_length() const
	{
		return  x*x + y*y + z*z;
	}

	void vec3::normalize()
	{
		GLfloat k = 1.0f / length();
		x *= k;
		y *= k;
		z *= k;
	}

	std::istream & operator>>(std::istream & is, vec3 & t)
	{
		is >> t.x >> t.y >> t.z;
		return is;
	}

	std::ostream & operator<<(std::ostream & os, const vec3 & t)
	{
		os << "vec3(" << t.x << "," << t.y << "," << t.z << ")";
		return os;
	}

	vec3 operator+(const vec3 & v1, const vec3 & v2)
	{
		return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	vec3 operator-(const vec3 & v1, const vec3 & v2)
	{
		return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	vec3 operator*(const vec3 & v1, const vec3 & v2)
	{
		return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}

	vec3 operator/(const vec3 & v1, const vec3 & v2)
	{
		return vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
	}

	vec3 operator*(const vec3 & v, GLfloat t)
	{
		return vec3(v.x * t, v.y * t, v.z * t);
	}

	vec3 operator*(GLfloat t, const vec3 & v)
	{
		return vec3(v.x * t, v.y * t, v.z * t);
	}

	vec3 operator/(const vec3 & v, GLfloat t)
	{
		return vec3(v.x / t, v.y / t, v.z / t);
	}

	GLfloat dot(const vec3 & v1, const vec3 & v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	vec3 cross(const vec3 & v1, const vec3 & v2)
	{
		return vec3(  (v1.y * v2.z - v1.z * v2.y),
					(-(v1.x * v2.z - v1.z * v2.x)),
					  (v1.x * v2.y - v1.y * v2.x));
	}

	vec3 normalize(vec3 v)
	{
		return v / v.length();
	}

	vec3 rodriguezFormula(vec3 v, vec3 around, GLfloat teta) {
		vec3 va = normalize(around);
		vec3 res = cos(teta) * v + sin(teta) * (cross(va, v)) + va*(dot(va, v)*(1 - cos(teta)));
		return res;
	}

	vec3 clean(vec3 v, GLfloat eps) {
		v.x = (fabs(v.x) < eps) ? 0.0f : v.x;
		v.y = (fabs(v.y) < eps) ? 0.0f : v.y;
		v.z = (fabs(v.z) < eps) ? 0.0f : v.z;
		return v;
	}

	vec3 lerp(vec3 start, vec3 finish, float rate)
	{
		std::max(0.0f, std::min(rate, 1.0f));
		return  (start + rate*(finish - start));
	}

	//------------------------------------------------------------------

	vec4::vec4(GLfloat e0, GLfloat e1, GLfloat e2, GLfloat e3)
	{
		x = e0;
		y = e1;
		z = e2;
		w = e3;
	}

	vec4::vec4(vec3 vector3, GLfloat e3)
	{
		x = vector3.x;
		y = vector3.y;
		z = vector3.z;
		w = e3;
	}

	vec4::vec4(GLfloat e0, vec3 vector3)
	{
		x = e0;
		y = vector3.x;
		z = vector3.y;
		w = vector3.z;
	}

	vec4::vec4(vec2 v1, vec2 v2)
	{
		x = v1.x;
		y = v1.y;
		z = v2.x;
		w = v2.y;
	}

	vec4::vec4(vec2 vector2, GLfloat e2, GLfloat e3)
	{
		x = vector2.x;
		y = vector2.y;
		z = e2;
		w = e3;
	}

	vec4::vec4(GLfloat e0, GLfloat e1, vec2 vector2)
	{
		x = e0;
		y = e1;
		z = vector2.x;
		w = vector2.y;
	}

	vec4::vec4(GLfloat e0, vec2 vector2, GLfloat e3)
	{
		x = e0;
		y = vector2.x;
		z = vector2.y;
		w = e3;
	}

	const vec4 & vec4::operator+() const
	{
		return *this;
	}

	vec4 vec4::operator-() const
	{
		return vec4(-x, -y, -z, -w);
	}

	GLfloat vec4::operator[](int i) const
	{
		if (i == 0) { return x; }
		else if (i == 1) { return y; }
		else if (i == 2) { return z; }
		else if (i == 3) { return w; }
		std::cerr << "Error invalid index operation for vec4" << std::endl;
		return INFINITY;
	}

	vec4 & vec4::operator+=(const vec4 & v2)
	{
		x += v2.x;
		y += v2.y;
		z += v2.z;
		w += v2.w;
		return *this;
	}

	vec4 & vec4::operator-=(const vec4 & v2)
	{
		x -= v2.x;
		y -= v2.y;
		z -= v2.z;
		w -= v2.w;

		return *this;
	}

	vec4 & vec4::operator*=(const vec4 & v2)
	{
		x *= v2.x;
		y *= v2.y;
		z *= v2.z;
		z *= v2.z;

		return *this;
	}

	vec4 & vec4::operator/=(const vec4 & v2)
	{
		x /= v2.x;
		y /= v2.y;
		z /= v2.z;
		w /= v2.w;

		return *this;
	}

	vec4 & vec4::operator*=(const GLfloat t)
	{
		x *= t;
		y *= t;
		z *= t;
		w *= t;

		return *this;
	}

	vec4 & vec4::operator/=(const GLfloat t)
	{
		GLfloat k = 1.0f / t;
		x *= k;
		y *= k;
		z *= k;
		w *= k;
		return *this;
	}

	GLfloat vec4::length() const
	{
		return sqrt(x*x + y*y + z*z + w*w);
	}

	GLfloat vec4::squared_length() const
	{
		return x*x + y*y + z*z + w*w;
	}

	void vec4::normalize()
	{
		GLfloat k = 1.0f / sqrt(x*x + y*y + z*z + w*w);
		x *= k;
		y *= k;
		z *= k;
		w *= k;
	}


	std::istream & operator>>(std::istream & is, vec4 & t)
	{
		is >> t.x >> t.y >> t.z >> t.w;
		return is;
	}

	std::ostream & operator<<(std::ostream & os, const vec4 & t)
	{
		os << "vec4(" << t.x << "," << t.y << "," << t.z << "," << t.w << ")";
		return os;
	}

	vec4 operator+(const vec4 & v1, const vec4 & v2)
	{
		return vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
	}

	vec4 operator-(const vec4 & v1, const vec4 & v2)
	{
		return vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
	}

	vec4 operator*(const vec4 & v1, const vec4 & v2)
	{
		return vec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
	}

	vec4 operator/(const vec4 & v1, const vec4 & v2)
	{
		return vec4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
	}

	vec4 operator*(const vec4 & v, GLfloat t)
	{
		return vec4(v.x * t, v.y * t, v.z * t, v.w * t);
	}

	vec4 operator*(GLfloat t, const vec4 &v) 
	{
		return vec4(v.x * t, v.y * t, v.z * t, v.w * t);
	}

	vec4 operator/(const vec4 & v, GLfloat t)
	{
		return vec4(v.x / t, v.y / t, v.z / t, v.w / t);
	}

	GLfloat dot(const vec4 & v1, const vec4 & v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	vec4 normalize(vec4 v)
	{
		return v / v.length();
	}

	const GLfloat * glFormat(vec4 v)
	{
		GLfloat aux[4] = { v.x,v.y,v.z, v.w };
		return aux;
	}

	glVec4::glVec4(vec4 v)
	{
		xyzw[0] = v.x;
		xyzw[1] = v.y;
		xyzw[2] = v.z;
		xyzw[3] = v.w;
	}
}
