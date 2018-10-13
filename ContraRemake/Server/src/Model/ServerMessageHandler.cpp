/*
 * ServerMessageHandler.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#include "ServerMessageHandler.hh"

ServerMessageHandler::ServerMessageHandler(ServerHandler* _server)
{
	server = _server;
}

void ServerMessageHandler::sendToAll(Message* message)
{
	server->sendToAll(message);
}

ServerMessageHandler::~ServerMessageHandler() {
	// TODO Auto-generated destructor stub
}

