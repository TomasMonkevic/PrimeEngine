#include "NetworkClient.h"
#ifdef _WIN32
//#include <winsock2.h>
#include <Ws2tcpip.h>
//#include <Windows.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

namespace PrimeEngine { namespace Networking {

	NetworkClient::NetworkClient(const char* ip, const char* port)
	{
#ifdef _WIN32
		WSADATA data;
#endif    
		sockaddr_in _serverAddress;
		unsigned int _port;
		_port = atoi(port);

		if ((_port < 1) || (_port > 65535)) 
		{
			throw "ERROR #1: invalid port specified.\n";
		}

#ifdef _WIN32
		WSAStartup(MAKEWORD(2, 2), &data);
#endif
		if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			throw "ERROR #2: cannot create socket.\n";
		}
		memset(&_serverAddress, 0, sizeof(_serverAddress));
		_serverAddress.sin_family = AF_INET;
		_serverAddress.sin_port = htons(_port);
#ifdef _WIN32
		if (inet_pton(AF_INET, ip, &(_serverAddress.sin_addr)) < 0)
		{
			throw "ERROR #3: Invalid remote IP address.\n";
		}
#else
		if (inet_aton(ip, &_serverAddress.sin_addr) <= 0)
		{
			throw "ERROR #3: Invalid remote IP address.\n";
		}
#endif
		if (connect(_socket, (sockaddr*)&_serverAddress, sizeof(_serverAddress))<0)
		{
			int error = WSAGetLastError();
			throw "ERROR #4: error in connect().\n";
		}
	}

	void NetworkClient::Send(const char* message)
	{
		send(_socket, message, strlen(message), 0);
	}

	const char* NetworkClient::Receive()
	{
		memset(_buffer, 0, BUFFER_LENGTH);
		recv(_socket, _buffer, BUFFER_LENGTH, 0);
		return _buffer;
	}

	void NetworkClient::Disconnect()
	{
#ifdef _WIN32
		closesocket(_socket);
#else
		close(_socket);
#endif
	}

}}