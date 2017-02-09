#include "Time.h"

namespace PrimeEngine
{
	Time::Time()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceCounter(&_startTime);
		QueryPerformanceFrequency(&frequency);
		_frequency = 1.0f / frequency.QuadPart;
	}

	void Time::Reset()
	{
		QueryPerformanceCounter(&_startTime);
	}

	float Time::Elapsed()
	{
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		unsigned __int64 cycles = current.QuadPart - _startTime.QuadPart;
		return (float)(cycles * _frequency);
	}

	unsigned int Time::GetFPS()
	{
		return 0;
	}
}