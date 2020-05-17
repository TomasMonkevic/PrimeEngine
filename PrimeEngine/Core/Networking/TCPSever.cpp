#ifdef _WIN32
#include <Ws2tcpip.h>
#endif
#include "TCPServer.h"

namespace PrimeEnginge { namespace Networking {

	TCPServer::TCPServer(unsigned port) :
		_port(port)
	{
#if _WIN32
		WSADATA data;
#endif
		_clientCount = 0;
		sockaddr_in servaddr;
		_maxFd = 0;
#if _WIN32
		int error = WSAStartup(MAKEWORD(2, 2), &data);
		if (error) 
		{
			printf("ERROR #1: WSAStartup failed with error: %d\n", error);
			getchar();
			exit(1);
		}
#endif
		if ((_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		{
#if _WIN32
			printf("ERROR #2: Failed to create listening socket. %d\n", WSAGetLastError());
#else
			printf("ERROR #2: Failed to create listening socket. %s\n", strerror(errno));
#endif
			getchar();
			exit(1);
		}

		memset(&servaddr, 0, sizeof(servaddr)); //set up the socket
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servaddr.sin_port = htons(_port);

		if (bind(_serverSocket, (sockaddr*)&servaddr, sizeof(servaddr)) < 0) 
		{
#if _WIN32
			printf("ERROR #3: Failed to bind listening socket. %d\n", WSAGetLastError());
#else
			printf("ERROR #3: Failed to bind listening socket. %s\n", strerror(errno));
#endif
			getchar();
			exit(1);
		}

		if (listen(_serverSocket, 5) < 0) 
		{
#if _WIN32
			printf("ERROR #4: Error in listen(). %d\n", WSAGetLastError());
#else
			printf("ERROR #4: Error in listen(). %s\n", strerror(errno));
#endif
			getchar();
			exit(1);
		}

		for (int i = 0; i < MAX_CLIENTS; i++) 
		{
			_clientSocket[i] = -1;
		}
	}

	int TCPServer::FindEmptyUser(SOCKET c_sockets[])
	{
		for (int i = 0; i < MAX_CLIENTS; i++) 
		{
			if (c_sockets[i] == -1) 
			{
				return i;
			}
		}
		return -1;
	}

	void TCPServer::AcceptConnections()
	{
		FD_ZERO(&_readSet);
		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			if (_clientSocket[i] != -1) 
			{
				FD_SET(_clientSocket[i], &_readSet);
				if (_clientSocket[i] > _maxFd)
				{
					_maxFd = (unsigned)_clientSocket[i];
				}
			}
		}

		FD_SET(_serverSocket, &_readSet); //selects next client
		if (_serverSocket > _maxFd)
		{
			_maxFd = (unsigned)_serverSocket;
		}

		select(_maxFd + 1, &_readSet, NULL, NULL, NULL);

		if (FD_ISSET(_serverSocket, &_readSet)) //accepts connection from clients
		{
			int client_id = FindEmptyUser(_clientSocket);
			if (client_id != -1) 
			{
				sockaddr_in clientaddr;
				int clientAddrLen = sizeof(clientaddr);
				memset(&clientaddr, 0, clientAddrLen);
				_clientSocket[client_id] = accept(_serverSocket, (sockaddr*)&clientaddr, &clientAddrLen);
				_clientCount++;
#ifdef _DEBUG
	#ifdef _WIN32
				char ip[16];
				inet_ntop(AF_INET, &clientaddr.sin_addr, ip, 16);
				printf("Connected:  %s\n", ip);
	#else
				printf("Connected:  %s\n", inet_ntoa(clientaddr.sin_addr));
	#endif // _WIN32
#endif // _DEBUG
			}
		}
	}

	void TCPServer::Send(unsigned clientId, const char* message, size_t size)
	{
		if (_clientSocket[clientId] != -1)
		{
			size_t len = send(_clientSocket[clientId], message, size, 0);
			if (len <= 0) //if failed to send data disconnect the client
			{
				DisconnectClient(clientId);
			}
		}
	}

	const char* TCPServer::Receive(unsigned clientId)
	{
		if (_clientSocket[clientId] != -1)
		{
			memset(_buffer, 0, BUFFER_LENGTH);
			int len = recv(_clientSocket[clientId], _buffer, BUFFER_LENGTH, 0);
			if (len <= 0)
			{
				return NULL;
			}
			return _buffer;
		}
		else
		{
			return NULL;
		}
	}

	void TCPServer::DisconnectClient(unsigned clientIndex)
	{
		if (_clientSocket[clientIndex] != -1) //to not disconnect the same client twice
		{
#if _WIN32
			closesocket(_clientSocket[clientIndex]);
#else
			close(_clientSocket[clientIndex]);
#endif
			_clientSocket[clientIndex] = -1;
			_clientCount--;
		}
	}
}}