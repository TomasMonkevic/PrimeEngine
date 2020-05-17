#pragma once

#include "NetworkEntity.h"
#include "../DllExport.h"
#if _WIN32
	#include <stdio.h>
#else
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <unistd.h>
	#include <errno.h>
#endif

#define BUFFER_LENGTH 1024
#define MAX_CLIENTS 50

namespace PrimeEnginge { namespace Networking {

	//Should work on Linux(not tested) and Windows
	class PRIMEENGINEAPI TCPServer
	{
	private:
		size_t _clientCount;
		unsigned _maxFd;
		char _buffer[BUFFER_LENGTH];
		SOCKET _serverSocket, _clientSocket[MAX_CLIENTS];
		unsigned _port;
		fd_set _readSet;
	public:
		TCPServer(unsigned port);
		int FindEmptyUser(SOCKET c_sockets[]);
		void AcceptConnections();
		void Send(unsigned clientId, const char* message, size_t size);
		const char* Receive(unsigned clientId);
		void DisconnectClient(unsigned clientIndex);

		inline size_t GetClientCount() const
		{
			return _clientCount;
		}
	};
}}

