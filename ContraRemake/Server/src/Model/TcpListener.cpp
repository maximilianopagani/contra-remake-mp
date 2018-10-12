#include "TcpListener.h"
using namespace std;


CTcpListener::CTcpListener(std::string ipAddress, int port)
	: m_ipAddress(ipAddress), m_port(port)
{
	clientSocket=0;
}

CTcpListener::~CTcpListener()
{
	Cleanup();
}

// Send a message to the specified client
void CTcpListener::Send(int clientSocket, std::string msg){

	strncpy(msj.nombre, "JOsue giovanni", 20);
	msj.dinero = 568415;
	msj.edad = 28;

	std::cout<<sizeof(msj)<<std::endl;
	send(clientSocket, (void *)&msj, sizeof(msj), 0);
	//send(clientSocket, msg.c_str(), msg.size() + 1, 0);
}

void CTcpListener::Send2(std::string msg){

	/*strncpy(msj.nombre, "JOsue giovanni", 20);
	msj.dinero = 568415;
	msj.edad = 28;*/

	//std::cout<<sizeof(msj)<<std::endl;
	//send(clientSocket, (void *)&msj, sizeof(msj), 0);
	send(clientSocket, msg.c_str(), msg.size() + 1, 0);

	char buf[MAX_BUFFER_SIZE];

	while(true){
		int bytesReceived = recv(clientSocket, buf, MAX_BUFFER_SIZE, 0);
		if (bytesReceived > 0){

			if(std::string(buf, 0, bytesReceived) == "ok"){
				//std::cout<<"Llego confirmacion"<<std::endl;
				break;
			}
		}
	}

}

// Initialize winsock
bool CTcpListener::Init()
{
	return true;
}

// The main processing loop
void CTcpListener::Run()
{
	char buf[MAX_BUFFER_SIZE];

	//aca podria poner a correr la logica del juego

	while (true)
	{
		// Create a listening socket
		int listening = CreateSocket();
		if (listening == -1)
		{
			//Error
			break;
		}

		int client = WaitForConnection(listening);
		if (client != -1)
		{
			close(listening);

			int bytesReceived = 0;
			do
			{
				//ZeroMemory(buf, MAX_BUFFER_SIZE);

				bytesReceived = recv(client, buf, MAX_BUFFER_SIZE, 0);
				if (bytesReceived > 0){

					if(std::string(buf, 0, bytesReceived) == "start"){
					Send(client, "ok");
					}
				}
				else {
					std::cout<<"Cliente Desconectado"<<std::endl;
				}

			} while (bytesReceived > 0);
			
			close(client);
		}

	}
}

int CTcpListener::clientAccept(){
	while (true){



		// Create a listening socket
		int listening = CreateSocket();

		if (listening == -1){
			//Error
			break;
		}

		//Espera a un cliente
		std::cout<<"Estoy esperando por un cliente"<<std::endl;
		int client = WaitForConnection(listening);
		std::cout<<"Estoy una linea despues del waitforConnection"<<std::endl;

		if (client != -1){
			//Encontro un cliente
			close(listening);
			clientSocket = client;


			return client;
		}
	}
	return -1 ;
}
int CTcpListener::recibir(int client){

	char buf[MAX_BUFFER_SIZE];

	int bytesReceived = recv(clientSocket, buf, MAX_BUFFER_SIZE, 0);

	if (bytesReceived > 0){

		if(std::string(buf, 0, bytesReceived) == "ok"){
			//Send(client, "ok");
		}

	}else{
		std::cout<<"Cliente Desconectado"<<std::endl;
	}

	return 0;
}

void CTcpListener::Cleanup()
{
	//WSACleanup();
}

// Create a socket
int CTcpListener::CreateSocket()
{
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening != -1)
	{
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(54000);
		//hint.sin_addr.s_addr = INADDR_ANY;
		inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);

		int bindOk = bind(listening, (sockaddr*)&hint, sizeof(hint));
		if (bindOk != -1)
		{
			std::cout<< "Se pudo bind el socket listening"<<std::endl;
			int listenOk = listen(listening, SOMAXCONN);
			if (listenOk == -1)
			{
				return -1;
			}
		}
		else
		{
			std::cout<< "No see pudo bind el socket listening"<<std::endl;
			return -1;
		}
	}

	return listening;
}

// Wait for a connection
int CTcpListener::WaitForConnection(int listening)
{
	int client = accept(listening, NULL, NULL);
	return client;
}
