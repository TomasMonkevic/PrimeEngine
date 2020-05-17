#pragma once

#if PRIME_WINDOWS
	#include <Windows.h>
#else
	#include <chrono>
#endif
#include "../DllExport.h"

namespace PrimeEngine 
{
	#if !PRIME_WINDOWS
	typedef std::chrono::high_resolution_clock primeClock;
	#endif

	class PRIMEENGINEAPI Time 
	{
	private:
#if PRIME_WINDOWS
		LARGE_INTEGER _startTime;
		double _frequency;
#else
	primeClock::time_point _startTime;
#endif
	public:
		Time();
		void Reset();
		float Elapsed();
	};
}
