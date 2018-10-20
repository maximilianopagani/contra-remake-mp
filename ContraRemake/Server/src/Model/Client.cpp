/*
 * Client.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: maximiliano
 */

#include "Client.hh"

Client::Client(int _socket, std::string _ip, int _port, std::string _username, std::string _password) // @suppress("Class members should be properly initialized")
{
	socket = _socket;
	ip = _ip;
	port = _port;
	username = _username;
	password = _password;
}

Client::~Client() {}

