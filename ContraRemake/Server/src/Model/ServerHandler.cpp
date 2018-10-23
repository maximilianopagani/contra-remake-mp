/*
 * ServerHandler.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#include "ServerHandler.hh"

ServerHandler::ServerHandler(int _port, int _max_clients) // @suppress("Class members should be properly initialized")
{
	max_clients = _max_clients;
	port = _port;
	listening_socket = -1;
}

bool ServerHandler::startServer()
{
	// CREO UN SOCKET PARA ESCUCHAR CONEXIONES DEL TIPO IPV4 Y STREAM
	listening_socket = socket(AF_INET, SOCK_STREAM, 0);

	// FALLA LA CREACION DEL SOCKET
	if(listening_socket == -1)
	{
		std::cout<<"ServerHandler: Falla al crear el socket de escucha inicial."<<std::endl;
		return false;
	}
	// ESTRUCTURA DE INFORMACION QUE DEFINE COMPORTAMIENTO DEL SOCKET PARA ESCUCHAR CONEXIONES "listening_socket"

	server_address.sin_family = AF_INET; // PROTOCOLO IVP4
	server_address.sin_addr.s_addr = INADDR_ANY; // TOMA LA IP ACTUAL DEL HOST
	server_address.sin_port = htons(port); // TRANSFORMO EL PUERTO A EL ORDEN DE BYTES ESTANDAR ESPERADO EN LAS REDES (BIG ENDIAN)

	// ASOCIO EL SOCKET QUE CREE PARA ESCUCHAR CONEXIONES CON UNA DIRECCION DE IP, PUERTO Y FAMILIA DE PROTOCOLO DEFINIDO ANTERIORMENTE
	if(bind(listening_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1)
	{
		std::cout<<"ServerHandler: Falla al asociar el socket de escucha con la estructura deseada."<<std::endl;
		return false;
	}

	// LE DIJO AL SOCKET QUE SE QUEDE ESCUCHANDO CONEXIONES ENTRANTES (HASTA max_clients CONEXIONES)
	if(listen(listening_socket, max_clients) == -1)
	{
		std::cout<<"ServerHandler: Falla al setear al socket en modo de espera de conexiones."<<std::endl;
		return false;
	}

	return true;
}

void ServerHandler::startListeningThread()
{
	pthread_create(&accept_connections_thread, NULL, &ServerHandler::acceptConnectionsThread, this);
}

// Para invocar un thread no se puede con un metodo común de un objeto, hay que llamar una funcion estática, y pasarle los objetos para luego llamar al método de instancia.
void* ServerHandler::acceptConnectionsThread(void* server)
{
	std::cout<<"ServerHandler: Iniciando acceptConnectionsThread."<<std::endl;
	((ServerHandler*)server)->acceptConnections();
	return nullptr;
}

struct thread_arg_struct {
	ServerHandler* arg_server;
	Client* arg_client;
};

// Metódo infinito, mediante un thread queda a la escucha de nuevas conexiones y las va a aceptar
// si la cantidad de jugadores conectados no alcanzó el máximo para esa partida
void ServerHandler::acceptConnections()
{
	while(true)
	{

		struct sockaddr_in client_address; // Estructura que me va a servir para guardar la informacion de la conexion entrante
		socklen_t address_size = sizeof(client_address);

		std::cout<<"ServerHandler: Invocando llamada bloqueante accept(). En espera de conexiones..."<<std::endl;

		// LLAMADA BLOQUEANTE. NO avanza hasta que no recibe y acepta una nueva conexión. Si salió todo OK, me devuelve el archivo
		// descriptivo de un NUEVO SOCKET creado exclusivamente para esa conexión (un integer). El socket original de escucha sigue escuchando, no se ve modificado.
		int new_socket = accept(listening_socket, (struct sockaddr*) &client_address, &address_size);
		// Guarda los datos de la conexion en la estructura client_address

		if(new_socket != -1) // Si salió todo OK
		{
			if(!this->isGameFull() || !this->allClientsOnline()) // Todavía no llegué a la cantidad de jugadores seteados para esa partida
			{
				// Creo nuevo cliente con los datos que obtuve de client_address. Es necesario hacer esas conversiones con las llamadas "inet_ntoa" y "n_tohs" ya que originalmente los datos
				// vienen en el formato de red estándar (big endian) y en mi maquina los quiero en (little endian)

				std::cout<<"ServerHandler: Conexión establecida con IP: "<<inet_ntoa(client_address.sin_addr)<<" - PUERTO: "<<ntohs(client_address.sin_port)<<std::endl;
				// Mando un mensaje al cliente recien conectado
				this->sendToSocket(new_socket, new MessageServer(INFO, NONE, "Te conectaste al servidor."));

				this->sendToSocket(new_socket, new MessageServer(REQUEST, LOGIN, "Solicito datos de login."));

				char msg[256];
				if(this->receiveOneMessageFromSocket(new_socket, msg, sizeof(msg)))
				{
					std::cout<<"ServerHandler - Recibo mensaje del cliente: "<<msg<<std::endl;

					std::string user;
					std::string passw;

					if(this->extractUserAndPasswFromMsg(new MessageServer(msg), user, passw))
					{
						std::cout<<"[ServerHandler] Extraigo User: "<<user<<" - Password: "<<passw<<std::endl;

						if(this->validateUserAndPassw(user, passw)) // si chequeo validacion user y passw es correcto
						{
							std::cout<<"[ServerHandler] Datos de login validados."<<std::endl;

							if(!this->alreadyOnline(user, passw))
							{
								std::cout<<"[ServerHandler] Chequeo si jugador ya está online OK."<<std::endl;

								if(!this->allClientsOnline() && this->alreadyLoggedBefore(user, passw))
								{
									std::cout<<"[ServerHandler] Entro en el caso para reconectar."<<std::endl;

									Client* reconnectClient = this->searchForClient(user, passw);

									std::cout<<"[ServerHandler] Encuentro cliente anterior para asociar."<<std::endl;

									if(reconnectClient != NULL)
									{
										if(this->isGameFull())
										{
											std::cout<<"[ServerHandler] El juego ya reservó todos los lugares para jugadores disponibles. Es una reconexión estandar con el juego ya comenzado."<<std::endl;

											MessageServer* reconnect_msg = new MessageServer(INFO, RECONNECT, "Info de reconnect para game.");
											reconnect_msg->setPlayerId(reconnectClient->getClientId());
											reconnect_msg->setUsername(reconnectClient->getUsername());
											pthread_mutex_lock(&server_mutex);
											server_recv_msgs_queue.push(reconnect_msg);
											pthread_mutex_unlock(&server_mutex);
											std::cout<<"[ServerHandler] Mensaje de reconexión enviado a game."<<std::endl;
										}
										else
										{
											std::cout<<"[ServerHandler] El juego todavía no reservó todos los lugares para jugadores disponibles. Estoy en etapa de espera de conexiones."<<std::endl;
										}

										reconnectClient->setOnline(new_socket);
										std::cout<<"[ServerHandler] Seteando cliente nuevamente online."<<std::endl;
										struct thread_arg_struct args;
										args.arg_server = this;
										args.arg_client = reconnectClient;
										std::cout<<"[ServerHandler] Creando nuevo thread de recepción de mensajes para el cliente."<<std::endl;
										pthread_create(reconnectClient->getRecieveMessagesThread(), NULL, &ServerHandler::recieveMessagesFromClientThread, (void*) &args);
									}
									else
									{
										this->sendToSocket(new_socket, new MessageServer(ERROR, RECONNECT, "Error raro al reconectar."));
										Utils::setDelay(300);
										shutdown(new_socket, SHUT_RDWR);
									}
								}
								else if(!this->isGameFull())
								{
									std::cout<<"[ServerHandler] El juego todavía no reservó todos los lugares para jugadores disponibles."<<std::endl;

									if(!this->alreadyLoggedBefore(user, passw))
									{
										std::cout<<"[ServerHandler] El usuario no ha logeado antes."<<std::endl;

										Client* new_client = new Client(new_socket, inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), user, passw);

										std::cout<<"[ServerHandler] Creado cliente con ID: "<<new_client->getClientId()<<std::endl;

										// Agrego el cliente a la lista de jugadores conectados
										pthread_mutex_lock(&server_clients_mutex);
										connectedClients.push_back(new_client);
										pthread_mutex_unlock(&server_clients_mutex);

										this->sendToSocket(new_socket, new MessageServer(INFO, WAITINGPLAYERS, "Informo login OK. Esperando."));

										// CREO UN THREAD DEDICADO A ESCUCHAR MENSAJES DE ESE NUEVO CLIENTE (PORQUE RECV ES UNA LLAMADA BLOQUEANTE Y ME BLOQUEARIA TODO SI UN CLIENTE NO MANDA NADA)
										struct thread_arg_struct args;
										args.arg_server = this;
										args.arg_client = new_client;

										std::cout<<"[ServerHandler] Creando nuevo thread de recepción."<<std::endl;

										pthread_create(new_client->getRecieveMessagesThread(), NULL, &ServerHandler::recieveMessagesFromClientThread, (void*) &args);

										// LOG DE EXITO
										// MANDAR PANTALLA DE ESPERANDO JUGADORES O LO QUE SEA ANTES DE ENTRAR A LA OTRA LLAMADA BLOQUEANTE DE ACCEPT
									}
									else
									{
										this->sendToSocket(new_socket, new MessageServer(ERROR, LOGIN_ALREADY_ON, "Usuario ya logeado."));
										Utils::setDelay(300);
										shutdown(new_socket, SHUT_RDWR);
									}
								}
								else
								{
									this->sendToSocket(new_socket, new MessageServer(ERROR, GAMEFULL, "Juego completo."));
									Utils::setDelay(300);
									shutdown(new_socket, SHUT_RDWR);
								}
							}
							else
							{
								this->sendToSocket(new_socket, new MessageServer(ERROR, LOGIN_ALREADY_ON, "Usuario online."));
								Utils::setDelay(300);
								shutdown(new_socket, SHUT_RDWR);
							}
						}
						else
						{
							this->sendToSocket(new_socket, new MessageServer(ERROR, LOGIN_DATA, "User y/o clave incorrectos."));
							Utils::setDelay(300);
							shutdown(new_socket, SHUT_RDWR);
						}
					}
					else
					{
						this->sendToSocket(new_socket, new MessageServer(ERROR, LOGIN_DATA, "Mensaje de login incorrecto."));
						Utils::setDelay(300);
						shutdown(new_socket, SHUT_RDWR);
					}
				}
				else
				{
					std::cout<<"[ServerHandler] Error al leer mensaje de login. Conexión perdida o apagada."<<std::endl;
					shutdown(new_socket, SHUT_RDWR);
				}
			}
			else
			{
				this->sendToSocket(new_socket, new MessageServer(ERROR, GAMEFULL, "Juego completo."));
				Utils::setDelay(300);
				shutdown(new_socket, SHUT_RDWR);
			}
		}
		else
		{
			std::cout<<"ServerHandler: Error al tratar de aceptar conexión entrante y crear nuevo socket."<<std::endl;
		}
	}
}

bool ServerHandler::readyToStartGame()
{
	if(this->isGameFull() && this->allClientsOnline())
		return true;
	else
		return false;
}

Client* ServerHandler::searchForClient(std::string user, std::string passw)
{
	for(uint i = 0; i < connectedClients.size(); i++)
	{
		if((connectedClients.at(i)->getUsername() == user) && (connectedClients.at(i)->getPassword() == passw))
			return connectedClients.at(i);
	}
	return NULL;
}

int ServerHandler::getConnectedClients()
{
	int clients_amount = 0;

	pthread_mutex_lock(&server_clients_mutex);
	clients_amount = connectedClients.size();
	pthread_mutex_unlock(&server_clients_mutex);

	return clients_amount;
}

bool ServerHandler::isGameFull()
{
	return (this->getConnectedClients() >= max_clients);
}

bool ServerHandler::allClientsOnline()
{
	int clients_size = this->getConnectedClients();

	for(uint i = 0; i < clients_size; i++)
	{
		if(connectedClients.at(i)->isOffline())
			return false;
	}
	return true;
}

bool ServerHandler::alreadyLoggedBefore(std::string user, std::string passw)
{
	for(uint i = 0; i < connectedClients.size(); i++)
	{
		if((connectedClients.at(i)->getUsername() == user) && (connectedClients.at(i)->getPassword() == passw))
			return true;
	}
	return false;
}

bool ServerHandler::alreadyOnline(std::string user, std::string passw)
{
	for(uint i = 0; i < connectedClients.size(); i++)
	{
		if((connectedClients.at(i)->getUsername() == user) && (connectedClients.at(i)->getPassword() == passw) && (connectedClients.at(i)->isOnline()))
			return true;
	}
	return false;
}

bool ServerHandler::validateUserAndPassw(std::string user, std::string passw) // HAY QUE METER LO DEL PARSER ACA
{
	if(user == "maxi" && passw == "maxi")
		return true;
	else if(user == "lucas" && passw == "lucas")
		return true;
	else if(user == "ignacio" && passw == "ignacio")
		return true;
	else if(user == "giovanni" && passw == "giovanni")
		return true;
	else if(user == "gino" && passw == "gino")
		return true;
	else
		return false;
}

bool ServerHandler::extractUserAndPasswFromMsg(MessageServer* message, std::string &user, std::string &passw)
{
	int MSG_HEADER_1, MSG_HEADER_2;
	char param1[32]; char param2[32]; char param3[32]; char param4[32];
	char msg[256];

	message->getContent(msg);
	std::cout<<"Game: handleEvents() - Procesando mensaje: "<<msg<<std::endl;

	sscanf(msg,"%i,%i,%[^,],%[^,],%[^,],%[^,];", &MSG_HEADER_1, &MSG_HEADER_2, param1, param2, param3, param4);

	if(MSG_HEADER_1 == INFO && MSG_HEADER_2 == LOGIN)
	{
		user = param1;
		passw = param2;
		return true;
	}
	else
		return false;
}

// Necesitaba pasarle por parametro el servidor, para que pueda ejecutar el método de la instancia, y el cliente para
// decirle para cual cliente voy a crear el thread de recepcion de mensajes
void* ServerHandler::recieveMessagesFromClientThread(void* arguments)
{
	struct thread_arg_struct* args = (struct thread_arg_struct*) arguments;;
	std::cout<<"ServerHandler: Iniciando recieveMessagesThread de cliente con IP: "<<(args->arg_client)->getIp()<<" y PUERTO: "<<(args->arg_client)->getPort()<<std::endl;
	(args->arg_server)->recieveMessagesFrom((args->arg_client));
	return nullptr;
}

bool ServerHandler::receiveOneMessageFromSocket(int socket, char* dest_char, int dest_char_size)
{
	int bytes_received = 0;

	bytes_received = recv(socket, dest_char, dest_char_size, 0); // LLAMADA BLOQUEANTE. NO avanza hasta recibir un mensaje

	if(bytes_received > 0)
		return true;
	else
		return false;
}

// Metodo infinito, siempre queda en la espera de recepcion de mensajes de ese cliente determinado
void ServerHandler::recieveMessagesFrom(Client* client)
{
	char buffer[256];
	int bytes_received = 0;

	while(true)
	{
		bytes_received = recv(client->getSocket(), buffer, sizeof(buffer), 0); // LLAMADA BLOQUEANTE. NO avanza hasta recibir un mensaje

		if(bytes_received > 0)
		{
			MessageServer* received_msg = new MessageServer(buffer);
			received_msg->setPlayerId(client->getClientId());
			received_msg->setUsername(client->getUsername());
			pthread_mutex_lock(&server_mutex);
			server_recv_msgs_queue.push(received_msg); // PUSHEO EL MENSAJE A LA COLA COMPARTIDA QUE ME SETEÓ GAME
			pthread_mutex_unlock(&server_mutex);

		}
		else if(bytes_received == -1)
		{
			std::cout<<"ServerHandler: Falla en recepción de mensaje."<<std::endl;
		}
		else if(bytes_received == 0) // solo funciona si cierro la cruz (que invoca al shutdown desde el cliente y esto lo detecta)
		{
			client->setOffline();

			if(this->isGameFull())
			{
				std::cout<<"Hubo shutdown desde cliente mientras el juego estaba lleno y corriendo."<<std::endl;
				MessageServer* disconnected_msg = new MessageServer(INFO, DISCONNECT, "Info de desconexion para game");
				disconnected_msg->setPlayerId(client->getClientId());
				disconnected_msg->setUsername(client->getUsername());
				pthread_mutex_lock(&server_mutex);
				server_recv_msgs_queue.push(disconnected_msg); // PUSHEO EL MENSAJE A LA COLA COMPARTIDA QUE ME SETEÓ GAME
				pthread_mutex_unlock(&server_mutex);
			}
			else
			{
				std::cout<<"Hubo shutdown desde cliente mientras el juego estaba en etapa de espera de conexiones."<<std::endl;
			}
			break;
		}
	}
}

void ServerHandler::getNewReceivedMessages(std::queue<MessageServer*>* store_in_queue)
{
	pthread_mutex_lock(&server_mutex);

	MessageServer* message;

	while(!server_recv_msgs_queue.empty())
	{
		message = server_recv_msgs_queue.front();
		server_recv_msgs_queue.pop();
		char msg[256];
		message->getContent(msg);
		std::cout<<"ServerHandler: Moviendo mensaje de cola de ServerHandler a cola de Game: "<<msg<<std::endl;
		store_in_queue->push(message);
	}

	pthread_mutex_unlock(&server_mutex);
}

void ServerHandler::sendToAllConnectedClients(MessageServer* message)
{
	for(int i = 0; i < max_clients; i++)
	{
		if(connectedClients.at(i)->isOnline())
		{
			char msg[256];
			message->getContent(msg);
			std::cout<<"ServerHandler: Mensaje enviado al cliente id "<<connectedClients.at(i)->getClientId()<<" : "<<msg<<std::endl;
			send(connectedClients.at(i)->getSocket(), msg, sizeof(msg), 0);
		}
	}
	delete message;
}

void ServerHandler::sendToConnectedClient(Client* client, MessageServer* message)
{
	if(client->isOnline())
	{
		char msg[256];
		message->getContent(msg);
		std::cout<<"ServerHandler: Mensaje enviado al cliente id "<<client->getClientId()<<" : "<<msg<<std::endl;
		send(client->getSocket(), msg, sizeof(msg), 0);
	}
	delete message;
}

void ServerHandler::sendToConnectedClientId(int client_id, MessageServer* message)
{
	if(connectedClients.at(client_id)->isOnline())
	{
		char msg[256];
		message->getContent(msg);
		std::cout<<"ServerHandler: Mensaje enviado al cliente id "<<client_id<<" : "<<msg<<std::endl;
		send(connectedClients.at(client_id)->getSocket(), msg, sizeof(msg), 0);
	}
	delete message;
}

void ServerHandler::sendToSocket(int destination_socket, MessageServer* message)
{
	char msg[256];
	message->getContent(msg);
	std::cout<<"ServerHandler: Mensaje enviado al socket: "<<msg<<std::endl;
	send(destination_socket, msg, sizeof(msg), 0);
	delete message;
}

ServerHandler::~ServerHandler() {}

