#pragma once

#include <string>
#include <vector>

namespace PrimeEngine {

	std::vector<std::string> SplitString(const std::string& string, const std::string& delimiters);
	char* Strtok(char* string, const char* delimeters, char** nextToken);
	char* Strdup(const char *src);
	int Sscanf(const char* buffer, const char* format, ...);
	int Sprintf(char* buffer, const char* format, ...);
}