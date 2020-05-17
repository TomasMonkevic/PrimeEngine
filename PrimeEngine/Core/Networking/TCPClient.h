#pragma once

#include <stdlib.h> 
#include "NetworkEntity.h"
#include "../DllExport.h"

#define BUFFER_LENGTH 1024

namespace PrimeEngine { namespace Networking {

	class PRIMEENGINEAPI NetworkClient : public NetworkEntity
	{
	private:
		int _socket;
		char _buffer[BUFFER_LENGTH];
	public:
		NetworkClient(const char* ip, const char* port);
		void Send(const char* message) override;
		const char* Receive() override;
		void Disconnect() override;
		int GetLastError() override;
	};
}}
