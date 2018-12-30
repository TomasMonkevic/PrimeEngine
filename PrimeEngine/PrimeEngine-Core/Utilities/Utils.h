#pragma once

#include <string>
#include <vector>
#include <DllExport.h>

namespace PrimeEngine {

	PRIMEENGINEAPI std::vector<std::string> SplitString(const std::string& string, const std::string& delimiters);
	PRIMEENGINEAPI char* Strtok(char* string, const char* delimeters, char** nextToken);
	PRIMEENGINEAPI char* Strdup(const char *src);
	PRIMEENGINEAPI int Sscanf(const char* buffer, const char* format, ...);
	PRIMEENGINEAPI int Sprintf(char* buffer, size_t numberOfElements, const char* format, ...);
}