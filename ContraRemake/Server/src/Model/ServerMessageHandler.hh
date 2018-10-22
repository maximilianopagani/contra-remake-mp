/*
 * ServerMessageHandler.hh
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#ifndef MODEL_SERVERMESSAGEHANDLER_HH_
#define MODEL_SERVERMESSAGEHANDLER_HH_

#include "../../Utils/MessageServer.hh"
#include "ServerHandler.hh"

class ServerMessageHandler
{
	public:

		ServerMessageHandler(ServerHandler* _server);
		virtual ~ServerMessageHandler();

		void sendToAllClients(MessageServer* message);

	private:

		ServerHandler* server;
};

#endif /* MODEL_SERVERMESSAGEHANDLER_HH_ */
