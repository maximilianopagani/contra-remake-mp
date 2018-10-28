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

void ServerMessageHandler::sendToClientId(int client_id, MessageServer* message)
{
	server->sendToConnectedClientId(client_id, message);
}

ServerMessageHandler::~ServerMessageHandler() {}

