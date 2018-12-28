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
		switch (color)
		{
			default:
			case ColorPrinter::White:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				break;
			case ColorPrinter::Red:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				break;
			case ColorPrinter::Green:
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			case ColorPrinter::Blue:
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				break;
		}
		va_list vaArgs;
		va_start(vaArgs, format);
		std::vprintf(format, vaArgs);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		va_end(vaArgs);
	}
}