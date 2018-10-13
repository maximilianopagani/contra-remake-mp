/*
 * Client.hh
 *
 *  Created on: Oct 13, 2018
 *      Author: maximiliano
 */

#ifndef MODEL_CLIENT_HH_
#define MODEL_CLIENT_HH_

#include <string>
#include <queue>
#include <thread>

class Client
{
	public:

		Client(int _socket, std::string _ip, int _port);
		virtual ~Client();

		int getSocket() { return socket; }
		std::string getIp() { return ip; }
		int getPort() { return port; }
		pthread_t* getRecieveMessagesThread() { return &receive_messages_thread; }

		void pushReceivedMessage(std::string message) { received_messages.push(message); }
		std::string getReceivedMessage() { return received_messages.front(); }
		void popReceivedMessage() { received_messages.pop(); }

	private:

		int socket, port;
		std::string ip;

		std::queue<std::string> received_messages;
		std::queue<std::string> sending_messages; // Aca se irían encolando los mensajes que quearmos ir enviando al cliente.
		// El asunto es que si a todos los clientes mando lo mismo, sería al pedo tener 4 colas iguales, quizas convenga una sola en Server,
		// aunque el envio va a ser distinto para cada cliente en la fase previa a que el cliente comience a jugar (pedido de datos de login, etc)

		pthread_t receive_messages_thread;
};

#endif /* MODEL_CLIENT_HH_ */