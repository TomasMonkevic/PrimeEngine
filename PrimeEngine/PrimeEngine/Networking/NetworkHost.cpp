#include "NetworkHost.h"
#ifdef _WIN32
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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
			throw "ERROR #1: invalid port specified.\n";
		}

#ifdef _WIN32
		WSAStartup(MAKEWORD(2, 2), &data);
#endif
		if ((l_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		{
			throw "ERROR #2: cannot create listening socket.\n";
		}
		memset(&_servaddr, 0, sizeof(_servaddr));
		_servaddr.sin_family = AF_INET;

		/*
		* Nurodomas IP adresas, kuriuo bus laukiama klientø, ðiuo atveju visi
		* esami sistemos IP adresai (visi interfeis'ai)
		*/
		_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		_servaddr.sin_port = htons(_port);

		/*
		* Serverio adresas susiejamas su socket'u
		*/
		if (bind(l_socket, (sockaddr*)&_servaddr, sizeof(_servaddr)) < 0) 
		{
			throw "ERROR #3: bind listening socket.\n";
		}

		/*
		* Nurodoma, kad socket'u l_socket bus laukiama klientø prisijungimo,
		* eilëje ne daugiau kaip 5 aptarnavimo laukiantys klientai
		*/
		if (listen(l_socket, 5) < 0) 
		{
			fprintf(stderr, "ERROR #4: error in listen().\n");
			exit(1);
		}
	}

	void NetworkHost::Listen()
	{
		sockaddr_in _clientaddr;
		memset(&_clientaddr, 0, sizeof(_clientaddr));
		_clientaddrlen = sizeof(sockaddr);
		if ((c_socket = accept(l_socket, (sockaddr*)&_clientaddr, &_clientaddrlen)) < 0)
		{
			throw "ERROR #5: error occured accepting connection.\n";
		}
	}

	void NetworkHost::Send(const char* message)
	{
		send(c_socket, message, strlen(message), 0);
	}

	const char* NetworkHost::Receive()
	{
		memset(&buffer, 0, sizeof(buffer));
		recv(c_socket, buffer, sizeof(buffer), 0);
		return buffer;
	}

	void NetworkHost::DisconnectClient()
	{
#ifdef _WIN32
		closesocket(c_socket);
#else
		close(c_socket);
#endif
	}

	void NetworkHost::DisconnectServer()
	{
#ifdef _WIN32
		closesocket(l_socket);
#else
		close(l_socket);
#endif
	}

	void NetworkHost::Disconnect()
	{
		DisconnectClient();
		DisconnectServer();
	}
}}