/*
 * ServerHandler.hh
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#ifndef MODEL_SERVERHANDLER_HH_
#define MODEL_SERVERHANDLER_HH_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <list>
#include "Client.hh"

extern pthread_mutex_t server_mutex;

class ServerHandler
{
	public:

		ServerHandler(int _port, uint _max_clients);
		virtual ~ServerHandler();

		bool startServer();
		void startListeningThread();
		void acceptConnections();

		void recieveMessagesFrom(Client* client);
		bool receiveOneMessageFromSocket(int socket, char* dest_char, int dest_char_size);
		bool extractUserAndPasswFromMsg(MessageServer* message, std::string &user, std::string &passw);
		bool validateUserAndPassw(std::string user, std::string passw);
		bool alreadyLogged(std::string user, std::string passw);

		void sendToClient(Client* client, MessageServer* message);
		void sendToAllClients(MessageServer* message);
		void sendToSocket(int destination_socket, MessageServer* message);

		int getConnectedClients() { return connectedClients.size(); }

		static void* acceptConnectionsThread(void* server);
		static void* recieveMessagesFromClientThread(void* client);

		void getNewReceivedMessages(std::queue<MessageServer*>* store_in_queue);

	private:

		int port;
		uint max_clients;

		struct sockaddr_in server_address;
		int listening_socket;

		pthread_t accept_connections_thread;

		std::list<Client*> connectedClients;
		std::list<Client*>::iterator connectedClientsIterator;

		std::queue<MessageServer*> server_recv_msgs_queue;
};

#endif /* MODEL_SERVERHANDLER_HH_ */
