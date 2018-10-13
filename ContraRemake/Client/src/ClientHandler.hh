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
#include "../../Common/Message.hh"

class ClientHandler
{
	public:

		ClientHandler();
		virtual ~ClientHandler();

		bool initSocket();
		bool connectToServer(std::string _server_ip, int _server_port);
		void sendToServer(Message* message);

		void recieveMessages();
		static void* recieveMessagesThread(void* client);

		void pushReceivedMessage(std::string message) { received_messages.push(message); }
		std::string getReceivedMessage() { return received_messages.front(); }
		void popReceivedMessage() { received_messages.pop(); }

	private:

		int network_socket, server_port;
		std::string server_ip;

		pthread_t receive_messages_thread;
		std::queue<std::string> received_messages;
};

#endif /* CLIENT_SRC_CLIENTHANDLER_HH_ */
