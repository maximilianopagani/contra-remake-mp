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
#include "../../../Common/Message.hh"
#include "Client.hh"

class ServerHandler
{
	public:

		ServerHandler(int _port, uint _max_clients);
		virtual ~ServerHandler();

		bool startServer();
		void acceptConnections();
		void recieveMessagesFrom(Client* client);

		void sendToClient(Client* client, Message* message);
		void sendToAll(Message* message);
		void sendToSocket(int destination_socket, Message* message);

		static void* acceptConnectionsThread(void* server);
		static void* recieveMessagesFromClientThread(void* client);

	private:

		int port;
		uint max_clients;

		struct sockaddr_in server_address;
		int listening_socket;

		std::list<Client*> connectedClients;
		std::list<Client*>::iterator connectedClientsIterator;
};

#endif /* MODEL_SERVERHANDLER_HH_ */
