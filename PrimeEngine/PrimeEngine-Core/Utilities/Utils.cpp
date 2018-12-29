#include "Utils.h"
#include <string.h>
#include <cstdarg>

namespace PrimeEngine 
{
	std::vector<std::string> SplitString(const std::string& string, const std::string& delimiters)
	{
		size_t start = 0;
		size_t end = string.find_first_of(delimiters);

		std::vector<std::string> result;

		while (end <= std::string::npos)
		{
			std::string token = string.substr(start, end - start);
			if (!token.empty())
				result.push_back(token);

			if (end == std::string::npos)
				break;

			start = end + 1;
			end = string.find_first_of(delimiters, start);
		}

		return result;
	}

	char* Strtok(char* string, const char* delimeters, char** nextToken)
	{
		#ifdef _WIN32
			return strtok_s(string, delimeters, nextToken);
		#else
			return strtok_r(string, delimeters, nextToken);
		#endif
	}

	char* Strdup(const char *src) 
	{
		size_t lenght = strlen(src) + 1;
		char* s = (char*)malloc(lenght);
		if (s == nullptr)
		{
			return nullptr;
		}
		return (char*)memcpy(s, src, lenght);
	}

	int Sscanf(const char* buffer, const char* format, ...)
	{
		va_list vaArgs;
		va_start(vaArgs, format);
		#ifdef _WIN32
			int result = vsscanf_s(buffer, format, vaArgs);
		#else
			int result = vsscanf(buffer, format, vaArgs);
		#endif
		va_end(vaArgs);
		return result;
	}

	int Sprintf(char* buffer, const char* format, ...)
	{
		va_list vaArgs;
		va_start(vaArgs, format);
		#ifdef _WIN32
			int result = vsprintf_s(buffer, format, vaArgs);
		#else
			int result = vsprintf(buffer, format, vaArgs);
		#endif
		va_end(vaArgs);
	}
}