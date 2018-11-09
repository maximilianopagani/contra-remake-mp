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
#include "../../Utils/Utils.hh"
#include "Client.hh"
#include "../../Utils/ServerParser.hh"

extern pthread_mutex_t server_mutex;
extern pthread_mutex_t server_clients_mutex;

class ServerHandler
{
	public:

		ServerHandler(int _port, int _max_clients, std::list<UserParser> users);
		virtual ~ServerHandler();

		bool startServer();
		void startListeningThread();
		bool isGameFull();
		void acceptConnections();

		void recieveMessagesFrom(Client* client);
		bool receiveOneMessageFromSocket(int socket, char* dest_char, int dest_char_size);
		bool extractUserAndPasswFromMsg(MessageServer* message, std::string &user, std::string &passw);
		bool validateUserAndPassw(std::string user, std::string passw);
		bool alreadyOnline(std::string user, std::string passw);
		bool alreadyLoggedBefore(std::string user, std::string passw);
		Client* searchForClient(std::string user, std::string passw);

		bool readyToStartGame();
		bool allClientsOnline();
		std::vector<string> getClientsUsernames();

		void sendToConnectedClient(Client* client, MessageServer* message, bool delete_message = true);
		void sendToConnectedClientId(int client_id, MessageServer* message);
		void sendToAllConnectedClients(MessageServer* message);
		void sendToSocket(int destination_socket, MessageServer* message);

		void pushReceivedMsgThreadSafe(MessageServer* message);
		void notifyGameOfDisconnection(Client* client);
		void notifyGameOfReconnection(Client* client);
		void processSendError(Client* client);
		int getConnectedClients();

		static void* acceptConnectionsThread(void* server);
		static void* recieveMessagesFromClientThread(void* client);

		void storeReceivedMsgsInExternalQueue(std::queue<MessageServer*>* store_in_queue);

	private:

		int port;
		int max_clients;
		std::list<UserParser> users;

		struct sockaddr_in server_address;
		int listening_socket;

		pthread_t accept_connections_thread;

		std::vector<Client*> connectedClients;
		std::queue<MessageServer*> server_recv_msgs_queue;
};

#endif /* MODEL_SERVERHANDLER_HH_ */
