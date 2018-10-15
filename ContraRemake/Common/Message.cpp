/*
 * Message.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: maximiliano
 */

#include "Message.hh"

Message::Message(std::string unique_param)
{
	std::strcpy(messageContent, unique_param.c_str());
	messageSize = sizeof(messageContent);
}

Message::Message(MsgDestHeader param1, MsgCmdHeader param2, std::string param3, std::string param4, std::string param5, std::string param6)
{
	std::string str = (std::to_string(param1) + "," + std::to_string(param2) + "," + param3 + "," + param4 + "," + param5 + "," + param6 + ";"); // @suppress("Function cannot be resolved")
	std::strcpy(messageContent, str.c_str());
	messageSize = sizeof(messageContent);
}

Message::Message(MsgDestHeader param1, MsgCmdHeader param2, int param3, int param4, int param5, int param6)
{
	std::string str = (std::to_string(param1) + "," + std::to_string(param2) + "," + std::to_string(param3) + "," + std::to_string(param4) + "," + std::to_string(param5) + "," + std::to_string(param6) + ";"); // @suppress("Function cannot be resolved")
	std::strcpy(messageContent, str.c_str());
	messageSize = sizeof(messageContent);
}
