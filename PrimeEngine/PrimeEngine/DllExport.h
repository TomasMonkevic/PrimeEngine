#ifndef DLL_EXPORT
#define DLL_EXPORT

#ifndef _DLL
#define PRIMEENGINEAPI __declspec(dllimport)
#else
#define PRIMEENGINEAPI __declspec(dllexport)
#endif

#endif // DLL_EXPORT

