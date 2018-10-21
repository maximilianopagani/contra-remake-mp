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

void ServerMessageHandler::sendToAllClients(MessageServer* message)
{
	server->sendToAllConnectedClients(message);
}

ServerMessageHandler::~ServerMessageHandler() {}

