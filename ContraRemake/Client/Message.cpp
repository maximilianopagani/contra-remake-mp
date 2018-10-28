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
}

Message::Message(MsgDestHeader header1, MsgCmdHeader header2, std::string param1, std::string param2, std::string param3, std::string param4)
{
	std::string str = (std::to_string(header1) + "," + std::to_string(header2) + "," + param1 + "," + param2 + "," + param3 + "," + param4 + ";"); // @suppress("Function cannot be resolved")
	std::strcpy(messageContent, str.c_str());
}

Message::Message(MsgDestHeader header1, MsgCmdHeader header2, int param1, int param2, int param3, int param4)
{
	std::string str = (std::to_string(header1) + "," + std::to_string(header2) + "," + std::to_string(param1) + "," + std::to_string(param2) + "," + std::to_string(param3) + "," + std::to_string(param4) + ";"); // @suppress("Function cannot be resolved")
	std::strcpy(messageContent, str.c_str());
}
