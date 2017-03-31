#ifndef DLL_EXPORT
#define DLL_EXPORT

#if _PRIME_ENGINE
#define PRIMEENGINEAPI __declspec(dllexport)
#else
#define PRIMEENGINEAPI __declspec(dllimport)
#endif

#endif // DLL_EXPORT

