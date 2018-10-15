/*
 * ServerMessageHandler.hh
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#ifndef MODEL_SERVERMESSAGEHANDLER_HH_
#define MODEL_SERVERMESSAGEHANDLER_HH_

#include "../../../Utils/Message.hh"
#include "ServerHandler.hh"

class ServerMessageHandler
{
	public:

		ServerMessageHandler(ServerHandler* _server);
		virtual ~ServerMessageHandler();

		void sendToAllClients(Message* message);
		void redirectRecievedMessage(Message* message);

	private:

		ServerHandler* server;
};

#endif /* MODEL_SERVERMESSAGEHANDLER_HH_ */
