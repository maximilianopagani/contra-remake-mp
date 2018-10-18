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

class ClientMessageHandler;

#include "ClientMessageHandler.hh"

class ClientHandler
{
	public:

		ClientHandler(ClientMessageHandler* _clientMessageHandler);
		virtual ~ClientHandler();

		bool initSocket();
		bool connectToServer(std::string _server_ip, int _server_port);
		void sendToServer(Message* message);
		void run();
		void quit();

		void recieveMessages();
		static void* recieveMessagesThread(void* client);
		pthread_t* getReceiveMessagesThread() { return &receive_messages_thread; }

		void processMessages();
		static void* processMessagesThread(void* client);
		pthread_t* getProcessMessagesThread() { return &process_messages_thread; }

	private:

		int network_socket, server_port;
		std::string server_ip;

		ClientMessageHandler* clientMessageHandler;

		pthread_t receive_messages_thread;
		pthread_t process_messages_thread;
		pthread_mutex_t client_mutex;

		std::queue<Message*> received_messages_queue;

		volatile bool running;
		//std::atomic<bool> stop_flag;
};

#endif /* CLIENT_SRC_CLIENTHANDLER_HH_ */
