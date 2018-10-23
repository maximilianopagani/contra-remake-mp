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
#include <mutex>
#include <atomic>

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

		void processMessages();
		static void* processMessagesThread(void* client);

		void setUsername(std::string _username);
		void setPassword(std::string _password);

		std::string getUsername();
		std::string getPassword();

	private:
		std::string username;
		std::string password;
		int network_socket, server_port;
		std::string server_ip;

		ClientMessageHandler* clientMessageHandler;

		// Threads con POSIX
		//pthread_t receive_messages_thread;
		//pthread_t process_messages_thread;
		//pthread_mutex_t client_mutex;
		//bool running = true;

		std::queue<Message*> received_messages_queue;

		// Threads con std:threads, std::mutex y std::atomic
		std::mutex client_mutex;
		std::atomic<bool> continue_flag {true};
};

#endif /* CLIENT_SRC_CLIENTHANDLER_HH_ */
