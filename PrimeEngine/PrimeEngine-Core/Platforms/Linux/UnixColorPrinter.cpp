#include "../../Utilities/ColorPrinter.h"
#include <cstdio>
#include <string.h>
#include <cstdarg>

using namespace PrimeEngine::Graphics;

namespace PrimeEngine
{
    void ColorPrinter::Print(const Color& color, const char* format, ...)
    {
        va_list vaArgs;
		va_start(vaArgs, format);
        char* colorFormat = new char[strlen(format)+32];
        switch(color.ToColor32())
        {
            case 0xFFFFFFFF: //White
                strcpy(colorFormat, "\033[37m");
                break;
            case 0xFF0000FF: //Red
                strcpy(colorFormat, "\033[31m");
                break;            
            case 0xFF00FF00: //Green
                strcpy(colorFormat, "\033[32m");
                break;            
            case 0xFFFF0000: //Blue
                strcpy(colorFormat, "\033[34m");
                break;       
            case 0xFF00FFFF: //Yellow
                strcpy(colorFormat, "\033[33m");
                break;         
            case 0xFFFF00FF: //Magenta
                strcpy(colorFormat, "\033[35m");
                break;  
            case 0xFFFFFF00: //Cyan
                strcpy(colorFormat, "\033[36m");
                break;  
            default: //default is white
                strcpy(colorFormat, "\033[0m");
                break;
        }
        strcat(colorFormat, format);
        strcat(colorFormat, "\033[0m");
		int result = vprintf(colorFormat, vaArgs);
		va_end(vaArgs);
        delete[] colorFormat;
    }
}