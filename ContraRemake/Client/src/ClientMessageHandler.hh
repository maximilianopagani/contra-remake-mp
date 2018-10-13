/*
 * ClientMessageHandler.hh
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#ifndef SRC_CLIENTMESSAGEHANDLER_HH_
#define SRC_CLIENTMESSAGEHANDLER_HH_

#include "../../Common/Message.hh"
#include "ClientHandler.hh"

class ClientMessageHandler
{
	public:

		ClientMessageHandler(ClientHandler* _client);
		virtual ~ClientMessageHandler();

		void sendToServer(Message* message);
		void redirectRecievedMessage(Message* message);

	private:

		ClientHandler* client;
};

#endif /* SRC_CLIENTMESSAGEHANDLER_HH_ */
