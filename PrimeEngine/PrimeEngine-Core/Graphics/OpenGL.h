#pragma once

#ifdef PE_ANDROID
	#include <GLES3/gl31.h>
#else
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
#endif

#if P_LOG_LEVEL >= PRIME_ERROR_L
#define GlCall(x) PrimeEngine::ClearGlErrors();\
	x;\
	PrimeEngine::LogGlCall(__FILE__, __LINE__)
#else
#define GlCall(x) x
#endif


namespace PrimeEngine {
	void ClearGlErrors();
	void LogGlCall(const char* file, int line);
}