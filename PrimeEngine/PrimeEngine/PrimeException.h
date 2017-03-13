#ifndef PRIME_EXCEPTION_H
#define PRIME_EXCEPTION_H

#include <exception>
#include "DllExport.h"

namespace PrimeEngine {

	class PRIMEENGINEAPI PrimeException : public std::exception
	{
	private:
		const char* _message;
		int _errorCode;
	public:
		PrimeException(const char* message, int errorCode = -1);
		const char* what() const throw();
		inline int GetErrorCode() const { return _errorCode; };
	};

}

#endif // !PRIME_EXCEPTION_H
