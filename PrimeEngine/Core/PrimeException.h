#pragma once

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