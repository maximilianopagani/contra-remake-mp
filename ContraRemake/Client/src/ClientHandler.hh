/*
 * ClientHandler.hh
 *
 *  Created on: Oct 13, 2018
 *      Author: maximiliano
 */

#ifndef CLIENT_SRC_CLIENTHANDLER_HH_
#define CLIENT_SRC_CLIENTHANDLER_HH_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include "ClientMessageHandler.hh"

class ClientHandler
{
	public:

		ClientHandler(ClientMessageHandler* _clientMessageHandler);
		virtual ~ClientHandler();

		bool initSocket();
		bool connectToServer(std::string _server_ip, int _server_port);
		void sendToServer(Message* message);

		void recieveMessages();
		static void* recieveMessagesThread(void* client);

		void processMessages();
		static void* processMessagesThread(void* client);

	private:

		int network_socket, server_port;
		std::string server_ip;

		ClientMessageHandler* clientMessageHandler;

		pthread_t receive_messages_thread;
		pthread_t process_messages_thread;
		pthread_mutex_t mutex;

		std::queue<Message*> received_messages_queue;
};

#endif /* CLIENT_SRC_CLIENTHANDLER_HH_ */
