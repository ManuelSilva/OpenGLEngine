#include "MatrixFactory.h"

using namespace EngineMath;



mat4 MatrixFactory::identity()
{
	return mat4(1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1);
}

mat4 MatrixFactory::TranslationMatrix(const vec3 v3)
{
	return mat4(1, 0, 0, v3.x,
		0, 1, 0, v3.y,
		0, 0, 1, v3.z,
		0, 0, 0, 1);
}

mat4 MatrixFactory::RodriguezMatrix(const vec3 a, const float teta) {
	mat3 A = mat3(0,-a.z,a.y,
				  a.z,0,-a.x,
				 -a.y,a.x,0);
	mat3 A2 = A*A;

	mat3 I = MatrixFactory::Mat4To3(MatrixFactory::identity());
	return  MatrixFactory::Mat3To4( I + A * (sin(teta)) + A2*(1-cos(teta)));
}

EngineMath::mat4 MatrixFactory::RotationXMatrix(const float teta)
{
	return EngineMath::mat4(1,0,0,0,
							0,cos(teta),-sin(teta),0,
							0,sin(teta),cos(teta),0,
							0,0,0,1);
}

mat4 MatrixFactory::RotationYMatrix(const float teta)
{
	return MatrixFactory::Mat3To4(mat3(cos(teta),0.0f,sin(teta),
										0.0f,1.0f,0.0f,
										-sin(teta),0.0f,cos(teta)));
}

EngineMath::mat4 MatrixFactory::RotationZMatrix(const float teta)
{
	return MatrixFactory::Mat3To4(mat3(cos(teta), -sin(teta), 0.0f,
									sin(teta), cos(teta), 0.0f,
									0.0f, 0.0f, 1.0f));
}

mat4 MatrixFactory::ScaleMatrix(const vec3 v3)
{
	return mat4(v3.x, 0, 0, 0,
		0, v3.y, 0, 0,
		0, 0, v3.z, 0,
		0, 0, 0, 1);
}

mat3 MatrixFactory::Mat4To3(const mat4 m4)
{
	return mat3(m4.m[0], m4.m[4], m4.m[8],
				m4.m[1], m4.m[5], m4.m[9],
				m4.m[2], m4.m[6], m4.m[10]);
}

mat4 MatrixFactory::Mat3To4(const mat3 m4)
{
	return mat4(m4.m[0], m4.m[3], m4.m[6],0,
				m4.m[1], m4.m[4], m4.m[7],0,
				m4.m[2], m4.m[5], m4.m[8],0,
				0,0,0,1);
}

mat4 MatrixFactory::PerspectiveMatrix(float fov, float aspect, float near, float far){
	float teta = fov/2.0f;
	float d = 1/tan(teta);
	return mat4(d/aspect,	0,						0,						0,
				0,			d,						0,						0,
				0,			0,	(near+far)/(near-far),(2*near*far)/(near-far),
				0,			0,	   				   -1, 						0);	
}

mat4 MatrixFactory::OrthographicMatrix(float left, float right, float top, float bottom, float near, float far){
	return mat4(2/(right-left),	0,				0,				(left+right)/(left-right),
				0,				2/(top-bottom),	0,				(bottom+top)/(bottom-top),
				0,				0,				2/(near-far),	(near+far)/(near-far),
				0,				0,				0,				1);
}

EngineMath::mat4 MatrixFactory::ViewMatrix(EngineMath::vec3 eye, EngineMath::vec3 center, EngineMath::vec3 up)
{
	vec3 zaxis = normalize(eye - center);
	vec3 xaxis = normalize(cross(up, zaxis));
	vec3 yaxis = cross(zaxis, xaxis);

	mat4 orientation(
		xaxis[0], yaxis[0], zaxis[0], 0,
		xaxis[1], yaxis[1], zaxis[1], 0,
		xaxis[2], yaxis[2], zaxis[2], 0,
		0, 0, 0, 1);

	mat4 translation(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-eye[0], -eye[1], -eye[2], 1);

	return orientation * translation;
}

unsigned int Numbers::giveId()
{
	return ++id_tracker;
}

EngineMath::vec4 Colors::hsv2rgb(float hue, float saturation, float value)
{
	double hh, p, q, t, ff;
	long i;
	EngineMath::vec4 out = EngineMath::vec4(0,0,0,1);

	if (saturation <= 0.0) {       // < is bogus, just shuts up warnings
		out.x = value;
		out.y = value;
		out.z = value;
		return out;
	}

	hh = hue;
	if (hh >= 360.0) hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = value * (1.0 - saturation);
	q = value * (1.0 - (saturation * ff));
	t = value * (1.0 - (saturation * (1.0 - ff)));

	switch (i) {
	case 0:
		out.x = value;
		out.y = t;
		out.z = p;
		break;
	case 1:
		out.x = q;
		out.y = value;
		out.z = p;
		break;
	case 2:
		out.x = p;
		out.y = value;
		out.z = t;
		break;

	case 3:
		out.x = p;
		out.y = q;
		out.z = value;
		break;
	case 4:
		out.x = t;
		out.y = p;
		out.z = value;
		break;
	case 5:
	default:
		out.x = value;
		out.y = p;
		out.z = q;
		break;
	}
	return out;
}
