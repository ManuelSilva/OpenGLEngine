#ifndef __ENGINE_MATH_H__
#define __ENGINE_MATH_H__
#include <math.h>
#ifndef __QUATERNIONS_H__
#include "Quaternion.h"
#endif // !__QUATERNIONS_H__

#ifndef __VEC_H__
	#include "vec.h"
#endif
#ifndef __MAT_H__
	#include "mat.h"
#endif 
#ifndef __MATRIX_FACTOTORY_H__
#include "MatrixFactory.h"
#endif 


#define PI 3.14159265358979323846f

class   EngineMath::vec2;
class   EngineMath::vec3;
class   EngineMath::vec4;
class   EngineMath::mat2;
class   EngineMath::mat3;
class   EngineMath::mat4;

#endif
