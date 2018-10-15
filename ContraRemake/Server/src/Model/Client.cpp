/*
 * Client.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: maximiliano
 */

#include "Client.hh"

Client::Client(int _socket, std::string _ip, int _port) // @suppress("Class members should be properly initialized")
{
	socket = _socket;
	ip = _ip;
	port = _port;
}

Client::~Client() {}

