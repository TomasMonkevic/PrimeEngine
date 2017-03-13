#ifndef PRIME_EXCEPTION_H
#define PRIME_EXCEPTION_H

#include "DllExport.h"

namespace PrimeEngine {

	class PRIMEENGINEAPI PrimeException
	{
	private:
		const char* _message;
		int _errorCode;
	public:
		PrimeException(const char* message, int errorCode);
		const char* what() const throw();
		inline int GetErrorCode() const { return _errorCode; };
	};

}

#endif // !PRIME_EXCEPTION_H
