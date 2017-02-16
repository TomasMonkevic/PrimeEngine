#ifndef DLL_EXPORT
#define DLL_EXPORT

#if _DLL
#define PRIMEENGINEAPI __declspec(dllexport)
#else
#define PRIMEENGINEAPI __declspec(dllimport)
#endif

#endif // DLL_EXPORT

