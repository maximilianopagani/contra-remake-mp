/*
 * ClientHandler.cpp
 *      Author: maximiliano
 */

#include "ClientHandler.hh"

ClientHandler::ClientHandler(ClientMessageHandler* _clientMessageHandler)
{
	username = "";
	password = "";
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
		LOGGER_ERROR("Falla al crear el socket de conexion inicial");
		return false;
	}

	return true;
}

bool ClientHandler::connectToServer(std::string _server_ip, int _server_port)
{
	if(network_socket == -1)
	{
		LOGGER_ERROR("Cliente no ha sido inicializado con initSocket(), o su inicialización ha fallado. Se aborta conexión.");
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
		LOGGER_ERROR("Falla al intentar conectar con el servidor de IP: " + server_ip + " y PUERTO: " + std::to_string(server_port));
		return false;
	}

	LOGGER_INFO("Conexion con el servidor exitosa");
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

	pthread_create(&receive_messages_thread, NULL, &ClientHandler::receiveMessagesThread, this);
	pthread_create(&process_messages_thread, NULL, &ClientHandler::processMessagesThread, this);

	pthread_join(receive_messages_thread, NULL);
	pthread_join(process_messages_thread, NULL);
}

void ClientHandler::receiveMessages()
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

void* ClientHandler::receiveMessagesThread(void* client)
{
	LOGGER_DEBUG("Iniciando receiveMessagesThread");
	((ClientHandler*)client)->receiveMessages();
	return nullptr;
}

void* ClientHandler::processMessagesThread(void* client)
{
	LOGGER_DEBUG("Iniciando processMessagesThread");
	((ClientHandler*)client)->processMessages();
	return nullptr;
}

void ClientHandler::sendToServer(Message* message)
{
	char msg[256];
	string sep = ": ";
	message->getContent(msg);
	LOGGER_DEBUG("Mensaje enviado al servidor" + sep + msg);
	send(network_socket, msg, 256, 0);
	delete message;
}

//========== IMPLEMENTACION CON std:threads, std::mutex y std::atomic =============

void ClientHandler::quit()
{
	continue_flag.store(false);
	shutdown(network_socket, SHUT_RDWR);
}

void ClientHandler::run()
{
	std::thread receive_thread (ClientHandler::receiveMessagesThread, this);
	std::thread process_thread (ClientHandler::processMessagesThread, this);

	receive_thread.join();
	process_thread.join();
}

void ClientHandler::pushReceivedMsgThreadSafe(Message* message)
{
    client_mutex.lock();
	received_messages_queue.push(message);
	client_mutex.unlock();
}

void ClientHandler::receiveMessages()
{
	char buffer[256];
	int bytes_received = 0;

	while(continue_flag.load())
	{
		bytes_received = recv(network_socket, buffer, sizeof(buffer), MSG_WAITALL); // LLAMADA BLOQUEANTE

		if(bytes_received > 0)
		{
			this->pushReceivedMsgThreadSafe(new Message(buffer));
		}
		else if(bytes_received == -1)
		{
			LOGGER_ERROR("Falla en recepción de mensaje.");
		}
		else if(bytes_received == 0)
		{
			LOGGER_INFO("Hubo shutdown desde el server, cerrando cliente");
			clientMessageHandler->processMessage(new Message(INFO, SERVER_CLOSED, 0));
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

		if(initPulse)
		{
			char msg[256];
			std::strcpy(msg, std::string("LATIDO").c_str());
			if(send(network_socket, msg, sizeof(msg), MSG_DONTWAIT) == -1)
			{
				if(errno == EAGAIN || errno == EWOULDBLOCK)
				{
					LOGGER_INFO("SE LLENÓ EL BUFFER DE SEND PARA EL SERVIDOR. SE PERDIO LA CONEXION. APAGANDO SOCKET. ");
					clientMessageHandler->processMessage(new Message(ERROR, LOST_CONNECTION, 0));
				}
			}
			Utils::setDelay(5);
		}
	}
}
