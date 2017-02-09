#ifndef TIMER_H
#define TIMER_H

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
		unsigned int GetFPS();
	};
}

#endif // !TIMER_H

