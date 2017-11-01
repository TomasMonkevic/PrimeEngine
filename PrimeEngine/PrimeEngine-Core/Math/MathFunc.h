#pragma once

#include <math.h> //standard math lib
#include <algorithm>
#include <DllExport.h>

namespace PrimeEngine { namespace Math {

	const double PI = 3.14159265;

	template<typename T>
	inline bool AreEqual(T left, T right, double errorTolerance = 0.0001)
	{
		return abs(left - right) < errorTolerance ? true : false;
	}

	inline float rsqrt(float value)
	{
		return 1.0f / std::sqrt(value);
	}

	inline float ToDegrees(float radians)
	{
		return radians * (180.0f / PI);
	}

	inline float ToRadians(float degrees)
	{
		return degrees * (PI / 180.0f);
	}
}}