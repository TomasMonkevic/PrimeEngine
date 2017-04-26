#ifndef PRIME_LOG
#define PRIME_LOG

#include <string.h>
#include <cstdio>
#include <Windows.h> //later move to platform specific folder

#define PRIME_INFO_L		0
#define PRIME_WARNING_L		1
#define PRIME_ERROR_L		2

namespace PrimeEngine 
{
	static void PlatformPrint(unsigned level, const char* message) //needs to be in a seperate file - platform specific
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		switch (level)
		{
		case PRIME_ERROR_L:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		case PRIME_WARNING_L:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		}
		std::printf("%s", message);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	static char _buffer[1024 * 10];

	static const char* ToString(const char* cString)
	{
		return cString;
	}

	static const char* ToString(const bool& t)
	{
		return t ? "true" : "false";
	}

	template<typename First>
	static void PrintInternal(unsigned& position, First first)
	{
		const char* formated = ToString(first);
		memcpy(&_buffer[position], formated, strlen(formated));
		position += strlen(formated);
	}

	template<typename First, typename... T>
	static void PrintInternal(unsigned& position, First first, T... args)
	{
		const char* formated = ToString(first);
		memcpy(_buffer[position], formated, strlen(formated));
		position += strlen(formated);
		if (sizeof...(args))
		{
			PrintInternal(position, args);
		}
	}

	template<typename... T>
	void LogMessage(unsigned level, T... message)
	{
		unsigned position = 0;
		PrintInternal(position, message...);
		PlatformPrint(level, _buffer);
	}
}

#ifdef P_DEBUG
	#define PRIME_ERROR(...) LogMessage(PRIME_ERROR_L, __VA_ARGS__)
#else
	#define PRIME_ERROR(...)
#endif

#endif // !PRIME_LOG

