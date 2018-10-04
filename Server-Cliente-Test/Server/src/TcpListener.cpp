#include "TcpListener.h"

#include <string.h>
void *memset(void *s, int c, size_t n);


CTcpListener::CTcpListener(std::string ipAddress, int port, MessageRecievedHandler handler){
	this->m_ipAddress = ipAddress;
	this->m_port = port;
	this->MessageReceived = handler;
}

CTcpListener::~CTcpListener()
{
	Cleanup();
}

// Send a message to the specified client
void CTcpListener::Send(int clientSocket, std::string msg)
{
	send(clientSocket, msg.c_str(), msg.size() + 1, 0);
}

// Initialize
bool CTcpListener::Init()
{ return true;
}

// Loop principial
void CTcpListener::Run()
{
	char buf[49152];

	while (true)
	{
		// Creo el socket que escucha
		int listening = CreateSocket();
		if (listening == -1)
		{
			break;
		}

		int client = WaitForConnection(listening);
		if (client != -1)
		{
			close(listening);

			int bytesReceived = 0;
			do{
				memset(buf,0, 49152);

				bytesReceived = recv(client, buf, MAX_BUFFER_SIZE, 0);
				if (bytesReceived > 0){

					 this->Send(client,"Como estas");

				}
				if(bytesReceived == 0){
					cout << "Client disconnected " << endl;

				}


			} while (bytesReceived > 0);
			
			close(client);
		}
	}


}

void CTcpListener::Cleanup(){

}

int CTcpListener::CreateSocket(){

	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening != -1)
	{
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(m_port);
		inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);

		int bindOk = bind(listening, (sockaddr*)&hint, sizeof(hint));
		if (bindOk != -1)
		{
			int listenOk = listen(listening, SOMAXCONN);
			if (listenOk == -1)
			{
				return -1;
			}
		}
		else{
			return -1;
		}
	}

	return listening;
}

//Espera por una coneccion
int CTcpListener::WaitForConnection(int listening){
	int client = accept(listening, NULL, NULL);
	return client;
}
