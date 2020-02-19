#pragma once

#ifdef PE_ANDROID
	#include <GLES3/gl31.h>
#else
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
#endif