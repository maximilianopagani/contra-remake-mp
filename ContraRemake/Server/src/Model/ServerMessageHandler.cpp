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

void ServerMessageHandler::sendToAllClients(Message* message)
{
	server->sendToAllClients(message);
}

ServerMessageHandler::~ServerMessageHandler() {}

