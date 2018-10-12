#pragma once

#include <string>
#include <string.h>
#include <iostream>
void *memset(void *s, int c, size_t n);
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define MAX_BUFFER_SIZE (49152)


class CTcpListener
{

public:

	// Constructor
	CTcpListener(std::string ipAddress, int port);

	// Destructor
	~CTcpListener();
	
	// Send a message to the specified client
	void Send(int clientSocket, std::string msg);
	void Send2(std::string msg);

	// Initialize winsock
	bool Init();

	// The main processing loop
	void Run();

	// Clean up after using the service
	void Cleanup();

	int clientAccept();

	int recibir(int client);

private:

	// Create a socket
	int CreateSocket();

	// Wait for a connection
	int WaitForConnection(int listening);

	// Address of the server
	std::string	m_ipAddress;

	// Listening port
	int	m_port;

	int clientSocket;

	//Structura del mensaje
	struct mensaje{
		char nombre[20];
		int edad;
		float dinero;
	};
	mensaje msj;
};
