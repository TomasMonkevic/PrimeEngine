#ifndef PRIME_LOG
#define PRIME_LOG

namespace PrimeEnginge 
{
	void PlatformPrint(unsigned level, const char* message) //needs to be in a seperate file
	{
		//print for windows - temp
	}

	template<class... T>
	void LogMessage(unsigned level, T... message)
	{

	}
}

#define PRIME_INFO_L		0
#define PRIME_WARNING_L		1
#define PRIME_ERROR_L		2

#ifdef P_DEBUG
	#define PRIME_ERROR(...) LogMessage(PRIME_ERROR_L, __VA_ARGS__)
#else
	#define PRIME_ERROR(...)
#endif

#endif // !PRIME_LOG

