#pragma once

#include "../DllExport.h"

namespace PrimeEngine { namespace Networking {

	//probably not needed
	class PRIMEENGINEAPI NetworkEntity
	{
	public:
		bool isHost;

		virtual void Send(const char* message) = 0;
		virtual const char* Receive() = 0;
		virtual void Disconnect() = 0;
		virtual int GetLastError() = 0;
	};
}}