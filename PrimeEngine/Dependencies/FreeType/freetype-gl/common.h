#pragma once

#ifdef WIN_32
    #define DLL_EXPORT __declspec(dllexport)
#else 
    #define DLL_EXPORT
#endif

