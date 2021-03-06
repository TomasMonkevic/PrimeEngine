#pragma once

//prime types
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>
#include <Graphics/Color.h>
#include <Math/Quaternion.h>
#include <Input.h>

#include <string>
#include <cstring>
#include <cstdio>
#include "ColorPrinter.h"
#include "Utils.h"
#ifdef PE_ANDROID
#include <android/log.h>
#endif

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

	static inline void PlatformPrint(unsigned level, const char* message) //needs to be in a seperate file - platform specific
	{
		#ifndef PE_ANDROID
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
        #else
		switch (level)
		{
			case PRIME_ERROR_L:
				__android_log_print(ANDROID_LOG_ERROR, "PrimeEngineAndroid", "%s", message);
				break;
			case PRIME_WARNING_L:
				__android_log_print(ANDROID_LOG_WARN, "PrimeEngineAndroid", "%s", message);
				break;
			default:
				__android_log_print(ANDROID_LOG_INFO, "PrimeEngineAndroid", "%s", message);
				break;
		}
		#endif
	}

	static const std::size_t BUFFER_SIZE = 1024 * 10;

	static char* const _buffer			= (char*)calloc(BUFFER_SIZE, sizeof(char));
	static char* const _formatBuffer	= (char*)calloc(BUFFER_SIZE, sizeof(char));

	#pragma region ToString functions
	template<typename T>
	inline const char* ToString(const T& number)
	{
		std::string formated = std::to_string(number);
		memcpy(_formatBuffer, formated.c_str(), formated.length() + 1);
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
	inline const char* ToString<std::string>(const std::string& string)
	{
		return string.c_str();
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
		PrimeEngine::Sprintf(_formatBuffer, BUFFER_SIZE, "%c", c);
		return _formatBuffer;
	}

	template<>
	inline const char* ToString<Math::Vector2>(const Math::Vector2& vec)
	{
		PrimeEngine::Sprintf(_formatBuffer, BUFFER_SIZE, "(%f, %f)", vec.x, vec.y);
		return _formatBuffer;
	}

	template<>
	inline const char* ToString<Input::TouchPhase>(const Input::TouchPhase& touchPhase)
	{
		switch (touchPhase)
		{
		case Input::TouchPhase::BEGAN:
			PrimeEngine::Sprintf(_formatBuffer, BUFFER_SIZE, "%s", "BEGAN");
			break;
		case Input::TouchPhase::MOVED:
			PrimeEngine::Sprintf(_formatBuffer, BUFFER_SIZE, "%s", "MOVED");
			break;
		case Input::TouchPhase::ENDED:
			PrimeEngine::Sprintf(_formatBuffer, BUFFER_SIZE, "%s", "ENDED");
			break;
		}
		return _formatBuffer;
	}

	template<>
	inline const char* ToString<Math::Vector3>(const Math::Vector3& vec)
	{
		PrimeEngine::Sprintf(_formatBuffer, BUFFER_SIZE, "(%f, %f, %f)", vec.x, vec.y, vec.z);
		return _formatBuffer;
	}

	template<>
	inline const char* ToString<Math::Vector4>(const Math::Vector4& vec)
	{
		PrimeEngine::Sprintf(_formatBuffer, BUFFER_SIZE, "(%f, %f, %f, %f)", vec.x, vec.y, vec.z, vec.w);
		return _formatBuffer;
	}

	template<>
	inline const char* ToString<Graphics::Color>(const Graphics::Color& col)
	{
		PrimeEngine::Sprintf(_formatBuffer, BUFFER_SIZE, "(%f, %f, %f, %f)", col[0], col[1], col[2], col[3]);
		return _formatBuffer;
	}

	template<>
	inline const char* ToString<Math::Quaternion>(const Math::Quaternion& q)
	{
		PrimeEngine::Sprintf(_formatBuffer, BUFFER_SIZE, "(%f, %f, %f, %f)", q[0], q[1], q[2], q[3]);
		return _formatBuffer;
	}

	template<>
	inline const char* ToString<Math::Matrix4x4>(const Math::Matrix4x4& q)
	{
		PrimeEngine::Sprintf(_formatBuffer, BUFFER_SIZE, "(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)", q[0][0], q[0][1], q[0][2], q[0][3],
			q[1][0], q[1][1], q[1][2], q[1][3],
			q[2][0], q[2][1], q[2][2], q[2][3],
			q[3][0], q[3][1], q[3][2], q[3][3]);
		return _formatBuffer;
	}
	#pragma endregion

	template<typename First>
	static void PrintInternal(unsigned& position, First first)
	{
		const char* formated = ToString(first);
		memcpy(&_buffer[position], formated, strlen(formated) + 1);
		position += strlen(formated);
	}

	template<typename First, typename... T>
	static void PrintInternal(unsigned& position, First&& first, T&&... args)
	{
		const char* formated = ToString(first);
		//if buffer is overfload -> reallocate
		memcpy(&_buffer[position], formated, strlen(formated) + 1);
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
	#define PRIME_ERROR(...) LogMessage(PRIME_ERROR_L, "[ERROR:", SplitString(__FILE__,"\\/").back(), '(', __LINE__, ")] ", __VA_ARGS__)
#else
	#define PRIME_ERROR(...)
#endif

#if P_LOG_LEVEL >= PRIME_WARNING_L
	#define PRIME_WARNING(...) LogMessage(PRIME_WARNING_L, "[WARNING:", SplitString(__FILE__,"\\/").back(), '(', __LINE__, ")] ", __VA_ARGS__)
#else
	#define PRIME_WARNING(...)
#endif

#if P_LOG_LEVEL >= PRIME_INFO_L
	#define PRIME_INFO(...) LogMessage(PRIME_INFO_L, "[INFO:", SplitString(__FILE__,"\\/").back(), '(', __LINE__, ")] ", __VA_ARGS__)
#else
	#define PRIME_INFO(...)
#endif

