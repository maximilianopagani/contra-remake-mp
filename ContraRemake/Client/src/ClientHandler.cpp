/*
 * ClientHandler.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: maximiliano
 */

#include "ClientHandler.hh"

ClientHandler::ClientHandler(ClientMessageHandler* _clientMessageHandler) // @suppress("Class members should be properly initialized")
{
	network_socket = -1;
	server_port = 0;
	server_ip = "";
	clientMessageHandler = _clientMessageHandler;
}

bool ClientHandler::initSocket()
{
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	if(network_socket == -1)
	{
		std::cout<<"ClientHandler: Falla al crear el socket de conexion inicial."<<std::endl;
		return false;
	}

	return true;
}

bool ClientHandler::connectToServer(std::string _server_ip, int _server_port)
{
	if(network_socket == -1)
	{
		std::cout<<"ClientHandler: Cliente no ha sido inicializado con initSocket(), o su inicialización ha fallado. Se aborta conexión."<<std::endl;
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
		std::cout<<"ClientHandler: Falla al intentar conectar con el servidor de IP: "<<server_ip.c_str()<<" y PUERTO: "<<server_port<<std::endl;
		return false;
	}

	std::cout<<"ClientHandler: Conexion con el servidor exitosa."<<std::endl;

	pthread_mutex_init(&mutex, NULL);

	pthread_create(&receive_messages_thread, NULL, &ClientHandler::recieveMessagesThread, this);
	pthread_create(&process_messages_thread, NULL, &ClientHandler::processMessagesThread, this);

	return true;
}

void* ClientHandler::recieveMessagesThread(void* client)
{
	std::cout<<"ClientHandler: Iniciando recieveMessagesThread."<<std::endl;
	((ClientHandler*)client)->recieveMessages();
	return nullptr;
}

void ClientHandler::recieveMessages()
{
	char buffer[256];
	int bytes_received = 0;

	while(true)
	{
		bytes_received = recv(network_socket, buffer, 256, 0); // LLAMADA BLOQUEANTE

		if(bytes_received > 0)
		{
	        pthread_mutex_lock(&mutex);

			received_messages_queue.push(new Message(buffer)); // Encolo mensajes a la cola de mensajes

			pthread_mutex_unlock(&mutex);
		}
		else if(bytes_received == -1)
		{
			std::cout<<"ClientHandler: Falla en recepción de mensaje."<<std::endl;
		}
	}
}

void* ClientHandler::processMessagesThread(void* client)
{
	std::cout<<"ClientHandler: Iniciando processMessagesThread."<<std::endl;
	((ClientHandler*)client)->processMessages();
	return nullptr;
}

void ClientHandler::processMessages()
{
	Message* message = NULL;

	while(true)
	{
		pthread_mutex_lock(&mutex);

		while(!received_messages_queue.empty())
		{
			message = received_messages_queue.front();
			received_messages_queue.pop();
			clientMessageHandler->redirectRecievedMessage(message);
		}

		pthread_mutex_unlock(&mutex);
	}
}

void ClientHandler::sendToServer(Message* message)
{
	char msg[256];
	message->getContent(msg);
	std::cout<<"ClientHandler: Mensaje enviado al servidor: "<<msg<<std::endl;
	send(network_socket, msg, 256, 0);
	delete message;
}

ClientHandler::~ClientHandler() {}
