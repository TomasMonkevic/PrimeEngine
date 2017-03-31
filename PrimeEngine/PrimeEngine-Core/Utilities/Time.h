#ifndef PRIME_TIMER_H
#define PRIME_TIMER_H

#include <Windows.h>
#include "..\DllExport.h"

namespace PrimeEngine 
{
	//Temporary only for windows. :(
	class PRIMEENGINEAPI Time 
	{
	private:
		LARGE_INTEGER _startTime;
		double _frequency;
	public:
		Time();
		void Reset();
		float Elapsed();
	};
}

#endif // !PRIME_TIMER_H

