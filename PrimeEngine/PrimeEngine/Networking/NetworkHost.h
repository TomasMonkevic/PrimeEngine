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
		int s_len;
		int r_len;
		char buffer[BUFFER_LENGTH];
		int l_socket; // socket'as skirtas prisijungimø laukimui
		int c_socket; // prisijungusio kliento socket'as
		unsigned int _port;
		int _clientaddrlen;
	public:
		NetworkHost(const char* port);
		//~NetworkHost();
		void Listen();
		void Send(const char* message) override;
		const char* Receive() override;
		void DisconnectClient();
		void DisconnectServer();
	};
}}

#endif // !NETWORK_HOST_H

