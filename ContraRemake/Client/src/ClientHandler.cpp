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
ClientHandler::~ClientHandler() {}

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
	return true;
}

//============================== IMPLEMENTACION CON THREADS POSIX =================================

/*

void ClientHandler::quit()
{
	pthread_mutex_lock(&client_mutex);
	running = false;
	pthread_mutex_unlock(&client_mutex);
}

void ClientHandler::run()
{
	client_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&client_mutex, NULL);

	pthread_create(&receive_messages_thread, NULL, &ClientHandler::recieveMessagesThread, this);
	pthread_create(&process_messages_thread, NULL, &ClientHandler::processMessagesThread, this);

	pthread_join(receive_messages_thread, NULL);
	pthread_join(process_messages_thread, NULL);
}

void ClientHandler::recieveMessages()
{
	char buffer[256];
	int bytes_received = 0;

	pthread_mutex_lock(&client_mutex);
	while(running)
	{
		pthread_mutex_unlock(&client_mutex);
		bytes_received = recv(network_socket, buffer, 256, 0); // LLAMADA BLOQUEANTE

		if(bytes_received > 0)
		{
	        pthread_mutex_lock(&client_mutex);
			received_messages_queue.push(new Message(buffer)); // Encolo mensajes a la cola de mensajes
			pthread_mutex_unlock(&client_mutex);
		}
		else if(bytes_received == -1)
		{
			std::cout<<"ClientHandler: Falla en recepción de mensaje."<<std::endl;
		}
	}
}

void ClientHandler::processMessages()
{
	Message* message = NULL;

	pthread_mutex_lock(&client_mutex);
	while(running)
	{
		//pthread_mutex_unlock(&client_mutex);
		//pthread_mutex_lock(&client_mutex);
		while(!received_messages_queue.empty())
		{
			message = received_messages_queue.front();
			received_messages_queue.pop();
			clientMessageHandler->processMessage(message);
		}
		pthread_mutex_unlock(&client_mutex);
	}
}
*/

void* ClientHandler::recieveMessagesThread(void* client)
{
	std::cout<<"ClientHandler: Iniciando recieveMessagesThread."<<std::endl;
	((ClientHandler*)client)->recieveMessages();
	return nullptr;
}

void* ClientHandler::processMessagesThread(void* client)
{
	std::cout<<"ClientHandler: Iniciando processMessagesThread."<<std::endl;
	((ClientHandler*)client)->processMessages();
	return nullptr;
}

void ClientHandler::sendToServer(Message* message)
{
	char msg[256];
	message->getContent(msg);
	std::cout<<"ClientHandler: Mensaje enviado al servidor: "<<msg<<std::endl;
	send(network_socket, msg, 256, 0);
	delete message;
}

//========== IMPLEMENTACION CON std:threads, std::mutex y std::atomic =============

void ClientHandler::quit()
{
	continue_flag.store(false);
}

void ClientHandler::run()
{
	std::thread receive_thread (ClientHandler::recieveMessagesThread, this);
	std::thread process_thread (ClientHandler::processMessagesThread, this);

	receive_thread.join();
	process_thread.join();
}

void ClientHandler::recieveMessages()
{
	char buffer[256];
	int bytes_received = 0;

	while(continue_flag.load())
	{
		bytes_received = recv(network_socket, buffer, 256, 0); // LLAMADA BLOQUEANTE

		if(bytes_received > 0)
		{
	        client_mutex.lock();
			received_messages_queue.push(new Message(buffer)); // Encolo mensajes a la cola de mensajes
			client_mutex.unlock();
		}
		else if(bytes_received == -1)
		{
			std::cout<<"ClientHandler: Falla en recepción de mensaje."<<std::endl;
		}
	}
}

void ClientHandler::processMessages()
{
	Message* message = NULL;

	while(continue_flag.load())
	{
		client_mutex.lock();
		while(!received_messages_queue.empty())
		{
			message = received_messages_queue.front();
			received_messages_queue.pop();
			clientMessageHandler->processMessage(message);
		}
		client_mutex.unlock();
	}
}
