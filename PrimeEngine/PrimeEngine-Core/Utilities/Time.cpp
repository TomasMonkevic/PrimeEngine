#include "Time.h"

namespace PrimeEngine
{
	Time::Time()
	{
#if PRIME_WINDOWS
		LARGE_INTEGER frequency;
		QueryPerformanceCounter(&_startTime);
		QueryPerformanceFrequency(&frequency);
		_frequency = 1.0f / frequency.QuadPart;
#else
		_startTime = primeClock::now();
#endif
	}

	void Time::Reset()
	{
#if PRIME_WINDOWS
		QueryPerformanceCounter(&_startTime);
#else
		_startTime = primeClock::now();
#endif
	}

	float Time::Elapsed()
	{
#if PRIME_WINDOWS
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		unsigned __int64 cycles = current.QuadPart - _startTime.QuadPart;
		return (float)(cycles * _frequency);
#else
		primeClock::time_point currentTime = primeClock::now();
		std::chrono::duration<float> elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - _startTime);
		return elapsedTime.count();
#endif
	}
}