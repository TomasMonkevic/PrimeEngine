#ifndef NETWORK_HOST_H
#define NETWORK_HOST_H

#include "../DllExport.h"
#include <stdlib.h>
#include "NetworkEntity.h"
#include <stdio.h>

#define BUFFER_LENGTH 1024

namespace PrimeEngine { namespace Networking {

	class PRIMEENGINEAPI NetworkHost : public NetworkEntity
	{
	private:
		char _buffer[BUFFER_LENGTH];
		int _listenSocket; // socket'as skirtas prisijungimu laukimui
		int _clientSocket; // prisijungusio kliento socket'as
		unsigned int _port;
	public:
		NetworkHost(const char* port);
		void Listen();
		void Send(const char* message) override;
		const char* Receive() override;
		void DisconnectClient();
		void DisconnectServer();
		void Disconnect() override;
		int GetLastError() override;
	};
}}

#endif // !NETWORK_HOST_H

