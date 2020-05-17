#pragma once

#if PRIME_WINDOWS
	#if _PRIME_ENGINE
		#define PRIMEENGINEAPI __declspec(dllexport)
	#else
		#define PRIMEENGINEAPI __declspec(dllimport)
	#endif
	#if PE_APP_IMPL
		#define PE_APP __declspec(dllexport)
	#else
		#define PE_APP __declspec(dllimport)
	#endif
#else
	#define PRIMEENGINEAPI
	#define PE_APP
#endif

#if PRIME_WINDOWS || PRIME_LINUX || PRIME_OSX
	#define PRIME_STANDALONE
#endif
