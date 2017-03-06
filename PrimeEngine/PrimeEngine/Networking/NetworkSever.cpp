#include "NetworkServer.h"
#if _WIN32
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
//#include <Ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#endif

namespace PrimeEngine { namespace Networking {

	NetworkServer::NetworkServer(const char* port)
	{
#if _WIN32
		WSADATA data;
#endif
		_clientCount = 0;
		sockaddr_in servaddr;
		maxfd = 0;
		_port = atoi(port);
		if ((_port < 1) || (_port > 65535)) 
		{
			throw "ERROR #1: invalid port specified.\n";
		}
#if _WIN32
		WSAStartup(MAKEWORD(2, 2), &data);
#endif
		if ((_listenSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			throw "ERROR #2: cannot create listening socket.\n";
		}

		memset(&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servaddr.sin_port = htons(_port);

		if (bind(_listenSocket, (sockaddr*)&servaddr, sizeof(servaddr))<0) 
		{
			throw "ERROR #3: bind listening socket.\n";
		}

		if (listen(_listenSocket, 5) <0) 
		{
			throw "ERROR #4: error in listen().\n";
		}

		for (int i = 0; i < MAX_CLIENTS; i++) 
		{
			_clientSocket[i] = -1;
		}
	}

	int NetworkServer::FindEmptyUser(int c_sockets[])
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

	void NetworkServer::AcceptConnections()
	{
		FD_ZERO(&read_set);
		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			if (_clientSocket[i] != -1) 
			{
				FD_SET(_clientSocket[i], &read_set);
				if (_clientSocket[i] > maxfd)
				{
					maxfd = _clientSocket[i];
				}
			}
		}

		FD_SET(_listenSocket, &read_set); //selects next client
		if (_listenSocket > maxfd)
		{
			maxfd = _listenSocket;
		}

		select(maxfd + 1, &read_set, NULL, NULL, NULL); //----

		if (FD_ISSET(_listenSocket, &read_set)) //accepts connection from clients
		{
			int client_id = FindEmptyUser(_clientSocket);
			if (client_id != -1) 
			{
				sockaddr_in clientaddr;
				clientaddrlen = sizeof(clientaddr);
				memset(&clientaddr, 0, clientaddrlen);
				_clientSocket[client_id] = accept(_listenSocket, (sockaddr*)&clientaddr, &clientaddrlen);
				_clientCount++;
#ifdef _WIN32
				char ip[16];
				inet_ntop(AF_INET, &clientaddr.sin_addr, ip, 16);
				printf("Connected:  %s\n", ip);
#else
				printf("Connected:  %s\n", inet_ntoa(clientaddr.sin_addr));
#endif
			}
		}
	}

	void NetworkServer::Send(unsigned int clientId, const char* message)
	{
		if (_clientSocket[clientId] != -1)
		{
			if (!message)
			{
				DisconnectClient(clientId);
				return;
			}
			int w_len = send(_clientSocket[clientId], message, strlen(message), 0);
			if (w_len <= 0)
			{
				DisconnectClient(clientId);
			}
		}
	}

	const char* NetworkServer::Receive(unsigned int clientId)
	{
		if (_clientSocket[clientId] != -1 && FD_ISSET(_clientSocket[clientId], &read_set))
		{
			memset(_buffer, 0, BUFFER_LENGTH);
			recv(_clientSocket[clientId], _buffer, BUFFER_LENGTH, 0);
			return _buffer;
		}
		else
		{
			return NULL;
		}
	}

	void NetworkServer::DisconnectClient(unsigned int clientIndex)
	{
#if _WIN32
		closesocket(_clientSocket[clientIndex]);
#else
		close(_clientSocket[clientIndex]);
#endif
		_clientSocket[clientIndex] = -1;
		_clientCount--;
	}
}}