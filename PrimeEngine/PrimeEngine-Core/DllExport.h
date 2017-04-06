#ifndef PRIME_DLL_EXPORT
#define PRIME_DLL_EXPORT

#if PRIME_WINDOWS
	#if _PRIME_ENGINE
		#define PRIMEENGINEAPI __declspec(dllexport)
	#else
		#define PRIMEENGINEAPI __declspec(dllimport)
	#endif
#else
	#define PRIMEENGINEAPI
#endif

#if PRIME_WINDOWS || PRIME_LINUX || PRIME_OSX
	#define PRIME_STANDALONE
#endif

#endif // PRIME_DLL_EXPORT

