/*
 * MessageServer.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#include "MessageServer.hh"

MessageServer::MessageServer(std::string unique_param)
{
	std::strcpy(messageContent, unique_param.c_str());
}

MessageServer::MessageServer(MsgHeader header1, MsgHeader header2, std::string param1, std::string param2, std::string param3, std::string param4)
{
	std::string str = (std::to_string(header1) + "," + std::to_string(header2) + "," + param1 + "," + param2 + "," + param3 + "," + param4 + ";");
	std::strcpy(messageContent, str.c_str());
}

MessageServer::MessageServer(MsgHeader header1, MsgHeader header2, int param1, int param2, int param3, int param4)
{
	std::string str = (std::to_string(header1) + "," + std::to_string(header2) + "," + std::to_string(param1) + "," + std::to_string(param2) + "," + std::to_string(param3) + "," + std::to_string(param4) + ";");
	std::strcpy(messageContent, str.c_str());
}
