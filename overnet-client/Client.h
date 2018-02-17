/*
	Multi-Client Computing (M2C).
	Client API.

	Version: 0.0.1
*/

#pragma once

#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

class Client
{
public:
	Client(std::string ipAddress, int port);
	~Client();

	std::string m_ipAddress;
	int m_port = 2000;
	SOCKET socket_client;
	sockaddr_in address;

	void Run( void (*onMessageReceivedHandler)(char *) );
	void RunServer();
	int SendBlock(int, int, int, int, int*);
	int Send(char*, int);


private:
	int InitWinsock();
	int CreateSocket();
	int Connect();
	void Cleanup();
};

