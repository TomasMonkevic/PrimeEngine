#include "../../Utilities/ColorPrinter.h"
#include <cstdio>
#include <string.h>
#include <cstdarg>
#include <windows.h>

namespace PrimeEngine
{
	//NOT FINISHED
	void ColorPrinter::Print(const PrimeEngine::Graphics::Color& color, const char* format, ...)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		switch (color.ToColor32())
		{
		default:
		case 0xFFFFFFFF: //White
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			break;
		case 0xFF0000FF: //Red
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		case 0xFF00FF00: //Green
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case 0xFFFF0000: //Blue
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			break;
		case 0xFF00FFFF: //Yellow
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case 0xFFFF00FF: //Magenta
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		case 0xFFFFFF00: //Cyan
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		}
		va_list vaArgs;
		va_start(vaArgs, format);
		std::vprintf(format, vaArgs);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		va_end(vaArgs);
	}
}