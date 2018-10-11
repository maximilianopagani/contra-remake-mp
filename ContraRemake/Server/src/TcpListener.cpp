#include "TcpListener.h"

CTcpListener::CTcpListener(std::string ipAddress, int port)
	: m_ipAddress(ipAddress), m_port(port)
{

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

// Initialize winsock
bool CTcpListener::Init()
{
	return true;
}

// The main processing loop
void CTcpListener::Run(int argc, char* argv[])
{
	char buf[MAX_BUFFER_SIZE];

	ServerParser* serverParser = new ServerParser();

	if (serverParser->loadConfiguration()) {
		LOGGER_INFO("Carga de configuracion del servidor aceptada");
		serverParser->testDataServerParser();
	} else {
		cout << "Carga de configuracion del servidor rechazada" << endl;
		// se mata al primer logger
		LOGGER_KILL();
		if (serverParser)
			delete serverParser;
		//return 1;
	}
	// se mata al primer logger
	LOGGER_KILL();

	int value = 0;
	ContraRemake* contraRemake = new ContraRemake();

	while (true)
	{
		// Create a listening socket
		int listening = CreateSocket();
		if (listening == -1)
		{
			break;
		}

		int client = WaitForConnection(listening);
		if (client != -1)
		{
			close(listening);

			std::cout<<"ANTESSSSSSSSSS"<<std::endl;
			value = contraRemake->init(argc,argv);
			std::cout<<"DESPUESSSSSSSSSS"<<std::endl;


			int bytesReceived = 0;
			do
			{
				//ZeroMemory(buf, MAX_BUFFER_SIZE);

				bytesReceived = recv(client, buf, MAX_BUFFER_SIZE, 0);
				if (bytesReceived > 0){

					Send(client, std::string(buf, 0, bytesReceived));
//					std::cout<<"ANTESSSSSSSSSS"<<std::endl;
//					value = contraRemake->init(argc,argv);
//					std::cout<<"DESPUESSSSSSSSSS"<<std::endl;

				}
				else {
					std::cout<<"Cliente Desconectado"<<std::endl;
				}

			} while (bytesReceived > 0);
			
			close(client);
		}

	}
	if (contraRemake) delete contraRemake;
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
		else
		{
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
