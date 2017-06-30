#ifndef PRIME_LOG
#define PRIME_LOG

//prime types
#include <Math/Vector3.h>
#include <Math/Vector4.h>
#include <Graphics\Color.h>

#include <string>
#include <cstdio>
#include <Windows.h> //later move to platform specific folder

#define PRIME_INFO_L		2
#define PRIME_WARNING_L		1
#define PRIME_ERROR_L		0

#ifndef P_LOG_LEVEL
	#define P_LOG_LEVEL 2
#endif // !P_LOG_LEVEL


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
	static char _formatBuffer[1024 * 10];

	#pragma region ToString functions
	template<typename T>
	static const char* ToString(const T& number)
	{
		std::string formated = std::to_string(number);
		memcpy(_formatBuffer, formated.c_str(), formated.length());
		const char* rez = _formatBuffer;
		return rez;
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

	template<>
	static const char* ToString<Math::Vector3>(const Math::Vector3& vec)
	{
		sprintf_s(_formatBuffer, "(%f, %f, %f)", vec.x, vec.y, vec.z);
		const char* rez = _formatBuffer;
		return rez;
	}

	template<>
	static const char* ToString<Math::Vector4>(const Math::Vector4& vec)
	{
		sprintf_s(_formatBuffer, "(%f, %f, %f, %f)", vec.x, vec.y, vec.z, vec.w);
		const char* rez = _formatBuffer;
		return rez;
	}

	template<>
	static const char* ToString<Graphics::Color>(const Graphics::Color& col)
	{
		sprintf_s(_formatBuffer, "(%f, %f, %f, %f)", col[0], col[1], col[2], col[3]);
		const char* rez = _formatBuffer;
		return rez;
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
		memset(_formatBuffer, 0, position);
	}
}

#if P_LOG_LEVEL >= PRIME_ERROR_L
	#define PRIME_ERROR(...) LogMessage(PRIME_ERROR_L, __VA_ARGS__)
#else
	#define PRIME_ERROR(...)
#endif

#if P_LOG_LEVEL >= PRIME_WARNING_L
	#define PRIME_WARNING(...) LogMessage(PRIME_WARNING_L, __VA_ARGS__)
#else
	#define PRIME_WARNING(...)
#endif

#if P_LOG_LEVEL >= PRIME_INFO_L
	#define PRIME_INFO(...) LogMessage(PRIME_INFO_L, __VA_ARGS__)
#else
	#define PRIME_INFO(...)
#endif

#endif // !PRIME_LOG

