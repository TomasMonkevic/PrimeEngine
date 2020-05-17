#include "TCPClient.h"
#include "../PrimeException.h"
#include <cstring>
#ifdef _WIN32
#include <Ws2tcpip.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#endif

namespace PrimeEngine { namespace Networking {

	NetworkClient::NetworkClient(const char* ip, const char* port)
	{
#ifdef _WIN32
		WSADATA data;
#endif  
		isHost = false;
		sockaddr_in _serverAddress;
		unsigned int _port;
		_port = atoi(port);

		if ((_port < 1) || (_port > 65535)) 
		{
			PrimeException invalidPort("Invalid port specified.", -1);
			throw invalidPort;
		}

#ifdef _WIN32
		WSAStartup(MAKEWORD(2, 2), &data);
#endif
		_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (_socket < 0)
		{
			PrimeException errorCreatingScoket("ERROR #2: cannot create socket.\n", GetLastError());
			throw errorCreatingScoket;
		}
		memset(&_serverAddress, 0, sizeof(_serverAddress));
		_serverAddress.sin_family = AF_INET;
		_serverAddress.sin_port = htons(_port);
#ifdef _WIN32
		if (inet_pton(AF_INET, ip, &(_serverAddress.sin_addr)) < 0)
		{
			PrimeException invalidIP("ERROR #3: Invalid remote IP address.\n", GetLastError());
			throw invalidIP;
		}
#else
		if (inet_aton(ip, &_serverAddress.sin_addr) <= 0)
		{
			PrimeException invalidIP("ERROR #3: Invalid remote IP address.\n", GetLastError());
			throw invalidIP;
		}
#endif
		if (connect(_socket, (sockaddr*)&_serverAddress, sizeof(_serverAddress))<0)
		{
			PrimeException connectionError("ERROR #4: error in connect().\n", GetLastError());
			throw connectionError;
		}
	}

	void NetworkClient::Send(const char* message)
	{
		send(_socket, message, (int)strlen(message), 0);
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

	int NetworkClient::GetLastError()
	{
#if _WIN32
		return WSAGetLastError();
#else
		return errno;
#endif // _WIN32
	}

}}