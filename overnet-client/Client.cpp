#include "Client.h"
#include "Overnet.h"
#include <fstream>

#define MAX_BUFFER 4096


Client::Client(std::string ipAddress, int port)
	: m_ipAddress(ipAddress), m_port(port)
{
	int wsResult = InitWinsock();
	if (wsResult != 0) {
		std::cerr << "Can't start winsock, Err #" << wsResult << std::endl;
	}
	else {
		int csResult = CreateSocket();
		if (csResult != 1) {
			int connResult = Connect();
			if (connResult == SOCKET_ERROR)
			{
				std::cerr << "Can't connect to server, Err #" << WSAGetLastError << std::endl;
				closesocket(socket_client);
				Cleanup();
			}
		}
	}

}


Client::~Client()
{
}

// Initialize winsock module
int Client::InitWinsock()
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	return wsResult;
}

// Create Socket
int Client::CreateSocket()
{
	socket_client = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_client == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError << std::endl;
		return 1;
	}

	// Fill in an address structure
	address.sin_family = AF_INET;
	address.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ipAddress.c_str(), &address.sin_addr);
	return 0;
}

// Connect to server
int Client::Connect() {
	int connResult = connect(socket_client, (sockaddr*)&address, sizeof(address));
	return connResult;
}

int Client::Send(char * data, int size) {
	int sendResult = send(socket_client, data, size, 0);
	return sendResult;
}

void Client::Run( void (*onMessageReceivedHandler)(char *) ) {
	int ReceivedBytes;
	char buffer[MAX_BUFFER];
	ZeroMemory(buffer, MAX_BUFFER);

	int messageSize = -1;
	int bytesOffset = 0;
	char* msgBuffer;

	while (true)
	{
		ReceivedBytes = recv(socket_client, buffer, MAX_BUFFER, 0);
		printf("[OVERNET] Received %d bytes.\n", ReceivedBytes);

		// If we received some data
		if (ReceivedBytes > 0)
		{
			// If this is a FIRST packet of full data
			if (messageSize < 0)
			{
				// Extract the full size of message
				memcpy(&messageSize, buffer, sizeof(messageSize));
				printf("[OVERNET] Full message size is %d bytes.\n", messageSize);

				// Init buffer for packed message
				msgBuffer = new char[messageSize];
				memset(msgBuffer, 0, messageSize);

				// Copy received pack to msgBuffer
				memcpy(msgBuffer, buffer, ReceivedBytes);
				bytesOffset += ReceivedBytes;
			}
			else { // If this is a NEXT packet
				memcpy(msgBuffer + bytesOffset, buffer, ReceivedBytes);
				bytesOffset += ReceivedBytes;
			}
			
			// Update Left to download size.
			messageSize -= ReceivedBytes;
			printf("[OVERNET] Left to receive %d bytes.\n", messageSize);
			memset(buffer, 0, MAX_BUFFER);

			if (messageSize == 0)
			{
				onMessageReceivedHandler(msgBuffer);
				messageSize = -1;
				bytesOffset = 0;
			}
		}
		else {
			break;
		}
	}

	closesocket(socket_client);
	Cleanup();
}

void Client::Cleanup()
{
	WSACleanup();
	puts("[OVERNET] Connection with host lost.\nPress any key to exit...");
}