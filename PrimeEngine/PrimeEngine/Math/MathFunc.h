#ifndef MATH_FUNC_H
#define MATH_FUNC_H

#include <math.h> //standard math lib

namespace PrimeEngine { namespace Math {

	inline float Abs(float value)
	{
		return value >= 0 ? value : value * -1;
	}

	inline bool AreEqual(float left, float right, float errorTolerance = 0.0001f)
	{
		return Abs(left - right) < errorTolerance ? true : false;
	}

}}

#endif // !MATH_FUNC_H