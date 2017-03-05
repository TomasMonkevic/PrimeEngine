#include <iostream>
#include <string>
#include <Networking\NetworkServer.h>

using std::cin;
using std::cout;
using std::endl;
using namespace PrimeEngine::Networking;

int main()
{
	try
	{
		std::string port;
		cout << "Enter server's port: ";
		cin >> port;
		NetworkServer server(port.c_str()); //server only works with 2 clients
		bool isMatch = false, isStarting = false;
		while (true)
		{
			server.AcceptConnections();
			if (server.GetClientCount() == 2)
			{
				if (!isMatch)
				{
					server.Send(0, "1"); //first player starts
					server.Send(1, "0");
					isMatch = true;
				}
				else
				{
					server.Send(!isStarting, server.Receive(isStarting));
					isStarting = !isStarting;
				}
			}
		}
	}
	catch(const char* msg)
	{
		cout << msg << endl;
		system("pause");
	}
	return 0;
}