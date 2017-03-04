#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H

#include "../DllExport.h"
#include <Ws2tcpip.h>

#define BUFFER_LENGTH 1024
#define MAX_CLIENTS 2

namespace PrimeEngine { namespace Networking {

	class PRIMEENGINEAPI NetworkServer //very poor multiclient server, needs a lot of improvements
	{
	private:
		size_t _clientCount;
		int clientaddrlen;
		int maxfd;
		char _buffer[BUFFER_LENGTH];
		int _listenSocket; // socket'as skirtas prisijungimu laukimui
		int _clientSocket[MAX_CLIENTS]; // prisijungusio kliento socket'as
		unsigned int _port;
		fd_set read_set;
	public:
		NetworkServer(const char* port);
		int FindEmptyUser(int c_sockets[]);
		void AcceptConnections();
		void Send(unsigned int clientId, const char* message);
		const char* Receive(unsigned int clientId);
		void DisconnectClient(unsigned int clientIndex);

		inline size_t GetClientCount()
		{
			return _clientCount;
		}
	};
}}

#endif // !NETWORK_SERVER_H

