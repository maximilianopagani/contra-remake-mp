/*
 * ClientHandler.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: maximiliano
 */

#include "ClientHandler.hh"

ClientHandler::ClientHandler() // @suppress("Class members should be properly initialized")
{
	network_socket = -1;
	server_port = 0;
	server_ip = "";
}

bool ClientHandler::initSocket()
{
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	if(network_socket == -1)
	{
		std::cout<<"Falla al crear el socket de conexion inicial."<<std::endl;
		return false;
	}

	return true;
}

bool ClientHandler::connectToServer(std::string _server_ip, int _server_port)
{
	if(network_socket == -1)
	{
		std::cout<<"Cliente no ha sido inicializado con initSocket(), o su inicialización ha fallado. Se aborta conexión."<<std::endl;
		return false;
	}

	server_ip = _server_ip;
	server_port = _server_port;

	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(server_port);
	server_address.sin_addr.s_addr = inet_addr(server_ip.c_str());

	if(connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1 )
	{
		std::cout<<"Falla al intentar conectar con el servidor de IP: "<<server_ip.c_str()<<" y PUERTO: "<<server_port<<std::endl;
		return false;
	}

	std::cout<<"Conexion con el servidor exitosa."<<std::endl;

	pthread_create(&receive_messages_thread, NULL, &ClientHandler::recieveMessagesThread, this);

	return true;
}

void* ClientHandler::recieveMessagesThread(void* client)
{
	std::cout<<"Iniciando recieveMessagesThread."<<std::endl;
	((ClientHandler*)client)->recieveMessages();
	return nullptr;
}

void ClientHandler::recieveMessages()
{
	char buffer[256];
	int bytes_received = 0;

	while(true)
	{
		bytes_received = recv(network_socket, buffer, sizeof(buffer), 0); // LLAMADA BLOQUEANTE

		if(bytes_received > 0)
		{
			this->pushReceivedMessage(buffer); // Encolo mensajes a la cola de mensajes
			std::cout<<"Mensaje del servidor recibido: "<<this->getReceivedMessage()<<std::endl; // Obtengo el mensaje mas antiguo de la cola (el primero en entrar)
			this->popReceivedMessage(); // Elimino el mensaje mas antiguo de la cola (el primero en entrar)

			// Encolar mensaje a una clase global? al message handler?
		}
		else if(bytes_received == -1)
		{
			std::cout<<"Falla en recepción de mensaje."<<std::endl;
		}
	}
}

void ClientHandler::sendToServer(Message* message)
{
	std::cout<<"Mensaje enviado al servidor: "<<message->getContent().c_str()<<std::endl;
	send(network_socket, message->getContent().c_str(), message->getSize()+1, 0);
}

ClientHandler::~ClientHandler() {
	// TODO Auto-generated destructor stub
}
