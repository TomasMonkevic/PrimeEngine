#include "PrimeException.h"

namespace PrimeEngine {

	PrimeException::PrimeException(const char* message, int errorCode) :
		_message(message), _errorCode(errorCode)
	{

	}

	const char* PrimeException::what() const throw()
	{
		return _message;
	}
}