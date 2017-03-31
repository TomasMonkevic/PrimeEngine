#include "NetworkHost.h"
#include "../PrimeException.h"
#ifdef _WIN32
//#include <winsock2.h>
#include <Ws2tcpip.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#endif

namespace PrimeEngine { namespace Networking {

	NetworkHost::NetworkHost(const char* port)
	{
#ifdef _WIN32
		WSADATA data;
#endif
		isHost = true;
		_port = atoi(port);
		sockaddr_in _servaddr;
		if ((_port < 1) || (_port > 65535))
		{
			PrimeException invalidPort("Invalid port specified.", -1);
			throw invalidPort;
		}

#ifdef _WIN32
		WSAStartup(MAKEWORD(2, 2), &data);
#endif
		_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (_listenSocket < 0)
		{
			PrimeException errorCreatingScoket("Cannot create socket.\n", GetLastError());
			throw errorCreatingScoket;
		}
		memset(&_servaddr, 0, sizeof(_servaddr));
		_servaddr.sin_family = AF_INET;

		/*
		* Nurodomas IP adresas, kuriuo bus laukiama klient�, �iuo atveju visi
		* esami sistemos IP adresai (visi interfeis'ai)
		*/
		_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		_servaddr.sin_port = htons(_port);

		/*
		* Serverio adresas susiejamas su socket'u
		*/
		if (bind(_listenSocket, (sockaddr*)&_servaddr, sizeof(_servaddr)) < 0)
		{
			PrimeException invalidIP("ERROR #3: Invalid remote IP address.\n", GetLastError());
			throw invalidIP;
		}

		/*
		* Nurodoma, kad socket'u l_socket bus laukiama klient� prisijungimo,
		* eil�je ne daugiau kaip 5 aptarnavimo laukiantys klientai
		*/
		if (listen(_listenSocket, 5) < 0)
		{
			PrimeException listenError("Error in liste()\n", GetLastError());
			throw listenError;
		}
	}

	void NetworkHost::Listen()
	{
		sockaddr_in _clientaddr;
		memset(&_clientaddr, 0, sizeof(_clientaddr));
		int _clientaddrlen = sizeof(sockaddr);
		_clientSocket = accept(_listenSocket, (sockaddr*)&_clientaddr, &_clientaddrlen);
		if (_clientSocket < 0)
		{
			PrimeException acceptError("ERROR #5: error occured accepting connection.\n", GetLastError());
			throw acceptError;
		}
	}

	void NetworkHost::Send(const char* message)
	{
		send(_clientSocket, message, (int)strlen(message), 0);
	}

	const char* NetworkHost::Receive()
	{
		memset(&_buffer, 0, sizeof(_buffer));
		recv(_clientSocket, _buffer, sizeof(_buffer), 0);
		return _buffer;
	}

	void NetworkHost::DisconnectClient()
	{
#ifdef _WIN32
		closesocket(_clientSocket);
#else
		close(_clientSocket);
#endif
	}

	void NetworkHost::DisconnectServer()
	{
#ifdef _WIN32
		closesocket(_listenSocket);
#else
		close(_listenSocket);
#endif
	}

	void NetworkHost::Disconnect()
	{
		DisconnectClient();
		DisconnectServer();
	}

	int NetworkHost::GetLastError()
	{
#if _WIN32
		return WSAGetLastError();
#else
		return errno;
#endif // _WIN32
	}
}}