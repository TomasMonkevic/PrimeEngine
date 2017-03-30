#ifndef DLL_EXPORT
#define DLL_EXPORT

#if PRIME_WINDOWS
	#if _PRIME_ENGINE
	#define PRIMEENGINEAPI __declspec(dllexport)
	#else
	#define PRIMEENGINEAPI __declspec(dllimport)
	#endif
#else
	#define PRIMEENGINEAPI
#endif

#endif // DLL_EXPORT

