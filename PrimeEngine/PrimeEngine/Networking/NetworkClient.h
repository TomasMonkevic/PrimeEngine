#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H


#include <stdlib.h> 
#include "NetworkEntity.h"
#include "../DllExport.h"

#define BUFFER_LENGTH 1024

namespace PrimeEngine { namespace Networking {

	class PRIMEENGINEAPI NetworkClient : public NetworkEntity
	{
	private:
		int _socket;
		char _buffer[BUFFER_LENGTH];
	public:
		NetworkClient(const char* ip, const char* port);
		//~NetworkClient();
		void Send(const char* message) override;
		const char* Receive() override;
		void Disconnect() override;
	};
}}

#endif // !NETWORK_CLIENT_H

