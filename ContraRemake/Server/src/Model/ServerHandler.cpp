/*
 * ServerHandler.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#include "ServerHandler.hh"

ServerHandler::ServerHandler(int _port, uint _max_clients)
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
		std::cout<<"Falla al crear el socket de escucha inicial."<<std::endl;
		return false;
	}
	// ESTRUCTURA DE INFORMACION QUE DEFINE COMPORTAMIENTO DEL SOCKET PARA ESCUCHAR CONEXIONES "listening_socket"

	server_address.sin_family = AF_INET; // PROTOCOLO IVP4
	server_address.sin_addr.s_addr = INADDR_ANY; // TOMA LA IP ACTUAL DEL HOST
	server_address.sin_port = htons(port); // TRANSFORMO EL PUERTO A EL ORDEN DE BYTES ESTANDAR ESPERADO EN LAS REDES (BIG ENDIAN)

	// ASOCIO EL SOCKET QUE CREE PARA ESCUCHAR CONEXIONES CON UNA DIRECCION DE IP, PUERTO Y FAMILIA DE PROTOCOLO DEFINIDO ANTERIORMENTE
	if(bind(listening_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1)
	{
		std::cout<<"Falla al asociar el socket de escucha con la estructura deseada."<<std::endl;
		return false;
	}

	// LE DIJO AL SOCKET QUE SE QUEDE ESCUCHANDO CONEXIONES ENTRANTES (HASTA max_clients CONEXIONES)
	if(listen(listening_socket, max_clients) == -1)
	{
		std::cout<<"Falla al setear al socket en modo de espera de conexiones."<<std::endl;
		return false;
	}

	return true;
}

// Para invocar un thread no se puede con un metodo común de un objeto, hay que llamar una funcion estática, y pasarle los objetos para luego llamar al método de instancia.
void* ServerHandler::acceptConnectionsThread(void* server)
{
	std::cout<<"Iniciando acceptConnectionsThread."<<std::endl;
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
		if(connectedClients.size() < max_clients) // Todavía no llegué a la cantidad de jugadores seteados para esa partida
		{
			struct sockaddr_in client_address; // Estructura que me va a servir para guardar la informacion de la conexion entrante
			socklen_t address_size = sizeof(client_address);

			std::cout<<"Invocando llamada bloqueante accept(). En espera de conexiones..."<<std::endl;

			// LLAMADA BLOQUEANTE. NO avanza hasta que no recibe y acepta una nueva conexión. Si salió todo OK, me devuelve el archivo
			// descriptivo de un NUEVO SOCKET creado exclusivamente para esa conexión (un integer). El socket original de escucha sigue escuchando, no se ve modificado.
			int new_socket = accept(listening_socket, (struct sockaddr*) &client_address, &address_size);
			// Guarda los datos de la conexion en la estructura client_address

			if(new_socket != -1) // Si salió todo OK
			{
				// Creo nuevo cliente con los datos que obtuve de client_address. Es necesario hacer esas conversiones con las llamadas "inet_ntoa" y "n_tohs" ya que originalmente los datos
				// vienen en el formato de red estándar (big endian) y en mi maquina los quiero en (little endian)
				Client* new_client = new Client(new_socket, inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

				std::cout<<"Conexión extablecida con un nuevo cliente. IP: "<<new_client->getIp()<<" - PUERTO: "<<new_client->getPort()<<std::endl;
				// Mando un mensaje al cliente recien conectado
				this->sendToClient(new_client, new Message(INFO, NONE, "Te conectaste al servidor."));

				// Agrego el cliente a la lista de jugadores conectados
				connectedClients.push_back(new_client);

				// CREO UN THREAD DEDICADO A ESCUCHAR MENSAJES DE ESE NUEVO CLIENTE (PORQUE RECV ES UNA LLAMADA BLOQUEANTE Y ME BLOQUEARIA TODO SI UN CLIENTE NO MANDA NADA)
				struct thread_arg_struct args;
				args.arg_server = this;
				args.arg_client = new_client;
				// Creo el thread para que se ejecute en la funcion indicada, y le paso los parametros, el server y el cliente.
				pthread_create(new_client->getRecieveMessagesThread(), NULL, &ServerHandler::recieveMessagesFromClientThread, (void*) &args);

				// LOG DE EXITO
				// MANDAR PANTALLA DE ESPERANDO JUGADORES O LO QUE SEA ANTES DE ENTRAR A LA OTRA LLAMADA BLOQUEANTE DE ACCEPT
			}
			else
			{
				std::cout<<"Error al tratar de aceptar conexión entrante y crear nuevo socket."<<std::endl;
			}
		}
	}
}

// Necesitaba pasarle por parametro el servidor, para que pueda ejecutar el método de la instancia, y el cliente para
// decirle para cual cliente voy a crear el thread de recepcion de mensajes
void* ServerHandler::recieveMessagesFromClientThread(void* arguments)
{
	struct thread_arg_struct* args = (struct thread_arg_struct*) arguments;;
	std::cout<<"Iniciando recieveMessagesThread de cliente con IP: "<<(args->arg_client)->getIp()<<" y PUERTO: "<<(args->arg_client)->getPort()<<std::endl;
	(args->arg_server)->recieveMessagesFrom((args->arg_client));
	return nullptr;
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
			client->pushReceivedMessage(buffer); // Encolo mensajes a la cola de mensajes de ese cliente
			std::cout<<"Mensaje de cliente recibido: "<<client->getReceivedMessage()<<std::endl; // Obtengo el mensaje mas antiguo de la cola (el primero en entrar)
			client->popReceivedMessage(); // Elimino el mensaje mas antiguo de la cola (el primero en entrar)

			// Encolar mensaje a una clase global? al message handler?
		}
		else if(bytes_received == -1)
		{
			std::cout<<"Falla en recepción de mensaje."<<std::endl;
		}
	}
}

void ServerHandler::sendToAll(Message* message) // Para enviar un mensaje a todos los clientes conectados
{
	// Itero por la lista de jugadores conectados, y les mando el mensaje mediante el socket que guardan dentro
	for(connectedClientsIterator = connectedClients.begin(); connectedClientsIterator != connectedClients.end();)
	{
	    this->sendToClient((*connectedClientsIterator), message);
	    ++connectedClientsIterator;
	}
}

void ServerHandler::sendToClient(Client* client, Message* message) // Para enviar un mensaje a un cliente conectado en particular
{
	std::cout<<"Mensaje enviado al cliente: "<<message->getContent().c_str()<<std::endl;
	send(client->getSocket(), message->getContent().c_str(), message->getSize()+1, 0);
}

void ServerHandler::sendToSocket(int destination_socket, Message* message) // Para enviar un mensaje a un socket en particular
{
	std::cout<<"Mensaje enviado al socket: "<<message->getContent().c_str()<<std::endl;
	send(destination_socket, message->getContent().c_str(), message->getSize()+1, 0);
}

ServerHandler::~ServerHandler() {}

