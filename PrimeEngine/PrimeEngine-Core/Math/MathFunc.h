#pragma once

#include <math.h> //standard math lib

namespace PrimeEngine { namespace Math {

	const double PI = 3.14159265;

	template<typename T>
	inline bool AreEqual(T left, T right, double errorTolerance = 0.0001)
	{
		return abs(left - right) < errorTolerance ? true : false;
	}

}}