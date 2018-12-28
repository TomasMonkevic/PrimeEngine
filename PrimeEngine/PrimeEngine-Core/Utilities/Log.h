#pragma once

//prime types
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>
#include <Graphics/Color.h>
#include <Math/Quaternion.h>


#include <string>
#include <cstring>
#include <cstdio>
#include "ColorPrinter.h"

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
		return string("[Unsupported type (") + typeid(T).name() + string(")!] (to_string)");
	}
}

namespace PrimeEngine 
{

	static void PlatformPrint(unsigned level, const char* message) //needs to be in a seperate file - platform specific
	{
		using namespace PrimeEngine::Graphics;

		switch (level)
		{
		case PRIME_ERROR_L:
			ColorPrinter::Print(Color::Red(), "%s", message);
			break;
		case PRIME_WARNING_L:
			ColorPrinter::Print(Color::Yellow(), "%s", message);
			break;
		default:
			ColorPrinter::Print(Color::White(), "%s", message);
			break;
		}
	}

	static const std::size_t BUFFER_SIZE = 1024 * 10;

	static char* const _buffer			= (char*)calloc(BUFFER_SIZE, sizeof(char));
	static char* const _formatBuffer	= (char*)calloc(BUFFER_SIZE, sizeof(char));

	#pragma region ToString functions
	template<typename T>
	inline const char* ToString(const T& number)
	{
		std::string formated = std::to_string(number);
		memcpy(_formatBuffer, formated.c_str(), formated.length());
		const char* rez = _formatBuffer;
		return rez;
	}

	template<>
	inline const char* ToString<char*>(char* const& cString)
	{
		return cString;
	}

	template<>
	inline const char* ToString<const char*>(const char* const& cString)
	{
		return cString;
	}

	template<>
	inline const char* ToString<const unsigned char*>(const unsigned char* const& openGLString)
	{
		return (const char*)openGLString;
	}

	template<>
	inline const char* ToString<bool>(const bool& b)
	{
		return b ? "true" : "false";
	}

	template<>
	inline const char* ToString<char>(const char& c)
	{
		#ifdef WIN_32
			sprintf_s(_formatBuffer, BUFFER_SIZE, "%c", c);
		#else
			sprintf(_formatBuffer, "%c", c);
		#endif
		return _formatBuffer;
	}

	template<>
	inline const char* ToString<Math::Vector2>(const Math::Vector2& vec)
	{
		#ifdef WIN_32
			sprintf_s(_formatBuffer, BUFFER_SIZE, "(%f, %f)", vec.x, vec.y);
		#else
			sprintf(_formatBuffer, "(%f, %f)", vec.x, vec.y);
		#endif
		return _formatBuffer;
	}

	template<>
	inline const char* ToString<Math::Vector3>(const Math::Vector3& vec)
	{
		#ifdef WIN_32
			sprintf_s(_formatBuffer, BUFFER_SIZE,"(%f, %f, %f)", vec.x, vec.y, vec.z);
		#else
			sprintf(_formatBuffer, "(%f, %f, %f)", vec.x, vec.y, vec.z);
		#endif
		return _formatBuffer;
	}

	template<>
	inline const char* ToString<Math::Vector4>(const Math::Vector4& vec)
	{
		#ifdef WIN_32
			sprintf_s(_formatBuffer, BUFFER_SIZE, "(%f, %f, %f, %f)", vec.x, vec.y, vec.z, vec.w);
		#else
			sprintf(_formatBuffer, "(%f, %f, %f, %f)", vec.x, vec.y, vec.z, vec.w);
		#endif
		return _formatBuffer;
	}

	template<>
	inline const char* ToString<Graphics::Color>(const Graphics::Color& col)
	{
		#ifdef WIN_32
			sprintf_s(_formatBuffer, BUFFER_SIZE, "(%f, %f, %f, %f)", col[0], col[1], col[2], col[3]);
		#else
			sprintf(_formatBuffer, "(%f, %f, %f, %f)", col[0], col[1], col[2], col[3]);
		#endif
		return _formatBuffer;
	}

	template<>
	inline const char* ToString<Math::Quaternion>(const Math::Quaternion& q)
	{
		#ifdef WIN_32
			sprintf_s(_formatBuffer, BUFFER_SIZE, "(%f, %f, %f, %f)", q[0], q[1], q[2], q[3]);
		#else
			sprintf(_formatBuffer, "(%f, %f, %f, %f)", q[0], q[1], q[2], q[3]);
		#endif
		return _formatBuffer;
	}

	template<>
	inline const char* ToString<Math::Matrix4x4>(const Math::Matrix4x4& q)
	{
		#ifdef WIN_32
			//TODO temp
			sprintf_s(_formatBuffer, BUFFER_SIZE, "(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)", q[0][0], q[0][1], q[0][2], q[0][3], 
				q[1][0], q[1][1], q[1][2], q[1][3], 
				q[2][0], q[2][1], q[2][2], q[2][3],
				q[3][0], q[3][1], q[3][2], q[3][3]);
		#else
			//TODO temp
			sprintf(_formatBuffer, "(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)", q[0][0], q[0][1], q[0][2], q[0][3], 
				q[1][0], q[1][1], q[1][2], q[1][3], 
				q[2][0], q[2][1], q[2][2], q[2][3],
				q[3][0], q[3][1], q[3][2], q[3][3]);
		#endif
		return _formatBuffer;
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
		//if buffer is overfload -> reallocate
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

