/*
 * Client.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: maximiliano
 */

#include "Client.hh"

int Client::CLIENT_ID_COUNTER = 0;

Client::Client(int _socket, std::string _ip, int _port, std::string _username, std::string _password) // @suppress("Class members should be properly initialized")
{
	socket = _socket;
	state = CLIENT_ONLINE;
	id = CLIENT_ID_COUNTER;
	++CLIENT_ID_COUNTER;
	ip = _ip;
	port = _port;
	username = _username;
	password = _password;
}

int Client::getSocket()
{
	int socket_to_return;

	pthread_mutex_lock(&server_clients_mutex);
	socket_to_return = socket;
	pthread_mutex_unlock(&server_clients_mutex);

	return socket_to_return;
}

bool Client::isOnline()
{
	bool online = false;

	pthread_mutex_lock(&server_clients_mutex);
	if(socket != -1 && state == CLIENT_ONLINE)
		online = true;
	pthread_mutex_unlock(&server_clients_mutex);

	return online;
}

bool Client::isOffline()
{
	bool offline = false;

	pthread_mutex_lock(&server_clients_mutex);
	if(socket == -1 && state == CLIENT_OFFLINE)
		offline = true;
	pthread_mutex_unlock(&server_clients_mutex);

	return offline;
}

void Client::setOnline(int connection_socket)
{
	pthread_mutex_lock(&server_clients_mutex);
	socket = connection_socket;
	state = CLIENT_ONLINE;
	pthread_mutex_unlock(&server_clients_mutex);
}

void Client::setOffline()
{
	pthread_mutex_lock(&server_clients_mutex);
	socket = -1;
	state = CLIENT_OFFLINE;
	pthread_mutex_unlock(&server_clients_mutex);
}

Client::~Client() {}

