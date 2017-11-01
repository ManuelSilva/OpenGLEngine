#include "Quaternion.h"

EngineMath::Quaternion::Quaternion()
{
	x = 0;
	y = 0;
	z = 0;

	t = 1;
}

EngineMath::Quaternion::~Quaternion()
{
}

EngineMath::Quaternion::Quaternion(float teta, vec4 axis)
{
	axis.normalize();
	float a = teta * (float)DEGREES_TO_RADIANS;
	t = cos(a / 2.0f);
	float s = sin(a / 2.0f);
	x = axis.x * s;
	y = axis.y * s;
	z = axis.z * s;

	clean();
	normalize();

}


void EngineMath::Quaternion::clean()
{
	if (fabs(t) < qThreshold) t = 0.0f;
	if (fabs(x) < qThreshold) x = 0.0f;
	if (fabs(y) < qThreshold) y = 0.0f;
	if (fabs(z) < qThreshold) z = 0.0f;
}

const float EngineMath::Quaternion::quadrance()
{
	return t*t + x*x + y*y + z*z;
}

const float EngineMath::Quaternion::norm()
{
	return sqrt(quadrance());
}

void EngineMath::Quaternion::normalize()
{
	float s = 1 / norm();
	x *= s;
	y *= s;
	z *= s;
	t *= s;
}

EngineMath::Quaternion EngineMath::Quaternion::conjugate()
{
	Quaternion qconj;
	qconj.t = t;
	qconj.x = -x;
	qconj.y = -y;
	qconj.z = -z;

	return qconj;
}

EngineMath::Quaternion EngineMath::Quaternion::inverse()
{
	return conjugate() * (1.0f / quadrance());
}

const EngineMath::vec4 EngineMath::Quaternion::getAngleAxis()
{

		vec4 axis;
		Quaternion qn;
		qn.x = x;
		qn.y = y;
		qn.z = z;
		qn.t = t;
		qn.normalize();

		float theta = 2.0f * acos(qn.t) * (float)RADIANS_TO_DEGREES;
		float s = sqrt(1.0f - qn.t*qn.t);
		if (s < qThreshold) {
			axis.x = 1.0f;
			axis.y = 0.0f;
			axis.z = 0.0f;
			axis.w = 1.0f;
		}
		else {
			axis.x = qn.x / s;
			axis.y = qn.y / s;
			axis.z = qn.z / s;
			axis.w = 1.0f;
		}
		return axis;
}

EngineMath::mat4 EngineMath::Quaternion::getMat()
{
	Quaternion qn;
	qn.x = x;
	qn.y = y;
	qn.z = z;
	qn.t = t;

	qn.normalize();

	float xx = qn.x * qn.x;
	float xy = qn.x * qn.y;
	float xz = qn.x * qn.z;
	float xt = qn.x * qn.t;
	float yy = qn.y * qn.y;
	float yz = qn.y * qn.z;
	float yt = qn.y * qn.t;
	float zz = qn.z * qn.z;
	float zt = qn.z * qn.t;
	mat4 matrix;

	matrix.m[0] = 1.0f - 2.0f * (yy + zz);
	matrix.m[1] = 2.0f * (xy + zt);
	matrix.m[2] = 2.0f * (xz - yt);
	matrix.m[3] = 0.0f;

	matrix.m[4] = 2.0f * (xy - zt);
	matrix.m[5] = 1.0f - 2.0f * (xx + zz);
	matrix.m[6] = 2.0f * (yz + xt);
	matrix.m[7] = 0.0f;

	matrix.m[8] = 2.0f * (xz + yt);
	matrix.m[9] = 2.0f * (yz - xt);
	matrix.m[10] = 1.0f - 2.0f * (xx + yy);
	matrix.m[11] = 0.0f;

	matrix.m[12] = 0.0f;
	matrix.m[13] = 0.0f;
	matrix.m[14] = 0.0f;
	matrix.m[15] = 1.0f;

	return matrix;
}


const EngineMath::Quaternion EngineMath::normalize(Quaternion q)
{
	float s = 1 / q.norm();
	return q * s;

}

std::ostream & EngineMath::operator<<(std::ostream & os, const Quaternion & t)
{
		os << "Quaternion: q(" << t.t << "," << t.x << "," << t.y << "," << t.z << ")" << std::endl;
		return os;
}


EngineMath::Quaternion EngineMath::operator*(const EngineMath::Quaternion & sq, const GLfloat & s)
{
	EngineMath::Quaternion q;
	q.t = s * sq.t;
	q.x = s * sq.x;
	q.y = s * sq.y;
	q.z = s * sq.z;

	return q;
}

EngineMath::Quaternion EngineMath::operator*(const EngineMath::Quaternion & q0, const EngineMath::Quaternion & q1)
{
	EngineMath::Quaternion q;
	q.t = q0.t * q1.t - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
	q.x = q0.t * q1.x + q0.x * q1.t + q0.y * q1.z - q0.z * q1.y;
	q.y = q0.t * q1.y + q0.y * q1.t + q0.z * q1.x - q0.x * q1.z;
	q.z = q0.t * q1.z + q0.z * q1.t + q0.x * q1.y - q0.y * q1.x;
	return q;
}

EngineMath::Quaternion EngineMath::operator+(const EngineMath::Quaternion & q0, const EngineMath::Quaternion & q1)
{
	EngineMath::Quaternion q;
	q.t = q0.t + q1.t;
	q.x = q0.x + q1.x;
	q.y = q0.y + q1.y;
	q.z = q0.z + q1.z;
	return q;
}



const EngineMath::Quaternion EngineMath::qLerp(const EngineMath::Quaternion & q0, const EngineMath::Quaternion & q1, float k)
{	
	float cos_angle = q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t;
	float k0 = 1.0f - k;
	float k1 = (cos_angle > 0) ? k : -k;
	
	Quaternion qi = (q0 * k0) + (q1 * k1);

	return normalize(qi);
}

const EngineMath::Quaternion EngineMath::qSlerp(const Quaternion & q0, const Quaternion & q1, float k)
{
	float angle = acos(q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t);
	float k0 = sin((1 - k)*angle) / sin(angle);
	float k1 = sin(k*angle) / sin(angle);
	Quaternion qi = (q0 * k0) + (q1 * k1);
	return normalize(qi);
}

