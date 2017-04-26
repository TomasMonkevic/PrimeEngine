#ifndef PRIME_LOG
#define PRIME_LOG

//add define for logging to be enabled

#include <string>
#include <cstdio>
#include <Windows.h> //later move to platform specific folder

#define PRIME_INFO_L		2
#define PRIME_WARNING_L		1
#define PRIME_ERROR_L		0

namespace std
{
	template<typename T>
	static string to_string(const T& arg)
	{
		return string("Type not suported");
	}
}

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

	#pragma region ToString functions
	template<typename T>
	static const char* ToString(const T& number)
	{
		return std::to_string(number).c_str();
	}

	template<>
	static const char* ToString<char*>(char* const& cString)
	{
		return cString;
	}

	template<>
	static const char* ToString<const char*>(const char* const& cString)
	{
		return cString;
	}

	template<>
	static const char* ToString<const unsigned char*>(const unsigned char* const& openGLString)
	{
		return (const char*)openGLString;
	}

	template<>
	static const char* ToString<bool>(const bool& b)
	{
		return b ? "true" : "false";
	}
	#pragma endregion

	template<typename First>
	static void PrintInternal(unsigned& position, First first)
	{
		const char* formated = ToString(first);
		memcpy(&_buffer[position], formated, strlen(formated));
		position += strlen(formated);
	}

	template<typename First, typename... T>
	static void PrintInternal(unsigned& position, First&& first, T&&... args)
	{
		const char* formated = ToString(first);
		memcpy(&_buffer[position], formated, strlen(formated));
		position += strlen(formated);
		if (sizeof...(args))
		{
			PrintInternal(position, std::forward<T>(args)...);
		}
	}

	template<typename... T>
	static void LogMessage(unsigned level, T... message)
	{
		unsigned position = 0;
		PrintInternal(position, std::forward<T>(message)...);
		PlatformPrint(level, _buffer);
		memset(_buffer, 0, position);
	}
}

#ifdef P_DEBUG
	#define PRIME_ERROR(...) LogMessage(PRIME_ERROR_L, __VA_ARGS__)
#else
	#define PRIME_ERROR(...)
#endif

#ifdef P_DEBUG
	#define PRIME_WARNING(...) LogMessage(PRIME_WARNING_L, __VA_ARGS__)
#else
	#define PRIME_WARNING(...)
#endif

#ifdef P_DEBUG
	#define PRIME_INFO(...) LogMessage(PRIME_INFO_L, __VA_ARGS__)
#else
	#define PRIME_INFO(...)
#endif

#endif // !PRIME_LOG

